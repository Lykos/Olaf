#ifndef THINKINGWRITER_H
#define THINKINGWRITER_H

#include "olaf/search/searchresult.h"
#include "olaf/rules/chessboard.h"
#include <chrono>
#include <atomic>

namespace olaf
{

class ThinkingWriter
{
public:
  ThinkingWriter();

  virtual ~ThinkingWriter();

  virtual void output(const ChessBoard& board,
                      const SearchResult& result,
                      const std::chrono::milliseconds& time,
                      int depth) = 0;

  void post(bool value);

  bool post() const;

private:
  std::atomic<bool> m_post;
};

} // namespace olaf

#endif // THINKINGWRITER_H
