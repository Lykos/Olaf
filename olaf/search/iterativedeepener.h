#ifndef ITERATIVEDEEPENER_H
#define ITERATIVEDEEPENER_H

#include <memory>
#include <mutex>

#include "olaf/search/searcher.h"
#include "olaf/search/searchresult.h"

namespace olaf
{

class AlphaBetaSearcher;
class SearchContext;
class ThinkingWriter;

class IterativeDeepener : public Searcher
{
public:
  IterativeDeepener(std::unique_ptr<AlphaBetaSearcher> searcher,
                    ThinkingWriter* writer,
                    depth_t min_depth,
                    score_t initial_window);

  SearchResult search(SearchContext* context) override;

  /**
   * @brief windowed_search performs a search which is expected to be close to the given score.
   */
  SearchResult windowed_search(SearchContext* context, score_t score);

private:
  std::unique_ptr<AlphaBetaSearcher> m_searcher;

  ThinkingWriter* const m_writer;

  const depth_t m_min_depth;

  const score_t m_initial_window;
};

} // namespace olaf

#endif // ITERATIVEDEEPENER_H
