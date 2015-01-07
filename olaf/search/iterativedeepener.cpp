#include "olaf/search/iterativedeepener.h"

#include <chrono>
#include <cassert>
#ifdef TRACE
#include <iostream>
#endif

#include "olaf/search/compositestopper.h"
#include "olaf/search/searchcontext.h"
#include "olaf/search/thinkingwriter.h"
#include "olaf/search/negamaxer.h"
#include "olaf/search/movegenerator.h"

using namespace std;
using namespace chrono;

namespace olaf
{

const SearchResult::score_t c_stable_margin = 50;

static bool results_stable(const vector<SearchResult> results) {
  if (results.size() < 3) {
    return false;
  }
  {
    const SearchResult::score_t a = (results.end() - 1)->score;
    const SearchResult::score_t b = (results.end() - 2)->score;
    const SearchResult::score_t c = (results.end() - 3)->score;
    const SearchResult::score_t min_seen = min(a, min(b, c));
    const SearchResult::score_t max_seen = max(a, max(b, c));
    if (max_seen - min_seen > c_stable_margin) {
      return false;
    }
  }
  {
    assert((results.end() - 1)->has_best_move);
    assert((results.end() - 2)->has_best_move);
    assert((results.end() - 3)->has_best_move);
    const Move a = (results.end() - 1)->best_move;
    const Move b = (results.end() - 2)->best_move;
    const Move c = (results.end() - 3)->best_move;
    return a == b && b == c;
  }
}

IterativeDeepener::IterativeDeepener(unique_ptr<NegaMaxer> searcher,
                                     ThinkingWriter* const writer,
                                     const depth_t min_depth,
                                     const score_t initial_window):
  m_searcher(move(searcher)),
  m_writer(writer),
  m_min_depth(min_depth),
  m_initial_window(initial_window)
{}

static const int c_leave_early_factor = 5;

SearchResult IterativeDeepener::search(SearchContext* context)
{
  steady_clock::time_point start = steady_clock::now();
  const SearchContext::DepthMode mode = context->depth_mode;
  depth_t max_depth = numeric_limits<depth_t>::max();
  switch (mode) {
    case SearchContext::DepthMode::ITERATIVE:
      context->search_depth = m_min_depth;
      context->depth_mode = SearchContext::DepthMode::FIXED_DEPTH;
      break;
    case SearchContext::DepthMode::FIXED_DEPTH:
      break;
    case SearchContext::DepthMode::MAX_DEPTH:
      max_depth = context->max_depth;
  }

  SearchResult result = m_searcher->search(context);
  if (!result.valid) {
    return SearchResult::invalid();
  }
  milliseconds time = duration_cast<milliseconds>(steady_clock::now() - start);
  m_writer->output(context->board, result, context->reconstruct_pv(), context->nodes, time, m_min_depth);
  if (result.terminal || mode == SearchContext::DepthMode::FIXED_DEPTH) {
    return result;
  }
  assert(result.has_best_move);
  // Now we have one move and can be more brutal for the weak stopper.
  CompositeStopper composite_stopper{context->forced_stopper, context->weak_stopper};
  context->forced_stopper = &composite_stopper;
  vector<SearchResult> results{result};
  while (context->search_depth < max_depth) {
    ++context->search_depth;
    SearchResult next_result = windowed_search(context, result.score);
    if (!next_result.valid) {
      break;
    }
    assert(next_result.has_best_move);
    result = next_result;
    milliseconds time = duration_cast<milliseconds>(steady_clock::now() - start);
    m_writer->output(context->board, result, context->reconstruct_pv(), context->nodes, time, context->search_depth);
    if (result.terminal) {
      break;
    }
    results.push_back(next_result);
    // If we understood the position, we can leave early.
    if (context->time_mode == SearchContext::TimeMode::ADAPTED
        && context->elapsed() * c_leave_early_factor > context->allocated_time
        && results_stable(results)) {
      break;
    }
  }
  return result;
}

SearchResult IterativeDeepener::windowed_search(SearchContext* context, const score_t score)
{
  score_t lower_window = m_initial_window;
  score_t upper_window = m_initial_window;
  while (true) {
    const score_t lower_bound = score - lower_window;
    const score_t upper_bound = score + upper_window;
#ifdef TRACE
    cout << "# Doing a windowed search between " << lower_bound << " and " << upper_bound << endl;
#endif
    const SearchResult result = m_searcher->search_windowed(context, lower_bound, upper_bound);
    if (!result.valid) {
      return result;
    }
    const score_t found_score = result.score;
    if (found_score <= lower_bound) {
#ifdef TRACE
  cout << "# Windowed search failed low." << endl;
#endif
      lower_window <<= 1;
    } else if (found_score >= upper_bound) {
#ifdef TRACE
  cout << "# Windowed search failed high." << endl;
#endif
      upper_window <<= 1;
    } else {
      return result;
    }
  }
}

} // namespace olaf
