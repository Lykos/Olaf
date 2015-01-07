#ifndef THINKINGWRITER_H
#define THINKINGWRITER_H

#include "olaf/search/searcher.h"

#include <chrono>
#include <atomic>
#include <vector>

namespace olaf
{

class ChessBoard;
class SearchResult;

class ThinkingWriter
{
public:
  ThinkingWriter();

  virtual ~ThinkingWriter();

  virtual void output(const ChessBoard& board,
                      const SearchResult& result,
                      const std::vector<Move>& main_variation,
                      int nodes,
                      const std::chrono::milliseconds& time,
                      Searcher::depth_t depth) = 0;

  void post(bool value);

  bool post() const;

private:
  std::atomic<bool> m_post;
};

} // namespace olaf

#endif // THINKINGWRITER_H
