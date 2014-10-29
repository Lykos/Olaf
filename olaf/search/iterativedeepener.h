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
                    depth_t min_depth);

  SearchResult search(SearchContext* context) override;

private:
  std::unique_ptr<AlphaBetaSearcher> m_searcher;

  ThinkingWriter* const m_writer;

  const depth_t m_min_depth;
};

} // namespace olaf

#endif // ITERATIVEDEEPENER_H
