#include "olaf/search/iterativedeepener.h"

#include <chrono>
#include <cassert>

#include "olaf/search/compositestopper.h"
#include "olaf/search/searchcontext.h"
#include "olaf/search/thinkingwriter.h"
#include "olaf/search/alphabetasearcher.h"

using namespace std;
using namespace chrono;

namespace olaf
{

IterativeDeepener::IterativeDeepener(unique_ptr<AlphaBetaSearcher> searcher,
                                     ThinkingWriter* const writer,
                                     const depth_t min_depth):
  m_searcher(move(searcher)),
  m_writer(writer),
  m_min_depth(min_depth)
{}

SearchResult IterativeDeepener::search(SearchContext* context)
{
  steady_clock::time_point start = steady_clock::now();
  const SearchContext::DepthMode mode = context->depth_mode;
  switch (mode) {
    case SearchContext::DepthMode::ITERATIVE:
      context->search_depth = m_min_depth;
      context->depth_mode = SearchContext::DepthMode::FIXED_DEPTH;
      break;
    case SearchContext::DepthMode::FIXED_DEPTH:
      break;
  }

  SearchResult result = m_searcher->search(context);
  if (!result.valid) {
    return SearchResult::invalid();
  }
  assert(!result.main_variation.empty());
  milliseconds time = duration_cast<milliseconds>(steady_clock::now() - start);
  m_writer->output(context->board, result, time, m_min_depth);
  if (mode == SearchContext::DepthMode::FIXED_DEPTH) {
    return result;
  }
  // Now we have one move and can be more brutal for the weak stopper.
  CompositeStopper composite_stopper{context->forced_stopper, context->weak_stopper};
  context->forced_stopper = &composite_stopper;
  while (true) {
    ++context->search_depth;
    const SearchResult& next_result =
        m_searcher->search(context);
    if (!next_result.valid) {
      break;
    }
    assert(!result.main_variation.empty());
    result.nodes += next_result.nodes;
    result.score = next_result.score;
    result.main_variation = std::move(next_result.main_variation);
    milliseconds time = duration_cast<milliseconds>(steady_clock::now() - start);
    m_writer->output(context->board, result, time, context->search_depth);
  }
  return result;

} // namespace olaf
}
