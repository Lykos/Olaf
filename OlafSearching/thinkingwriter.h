#ifndef THINKINGWRITER_H
#define THINKINGWRITER_H

#include "searchresult.h"
#include "OlafRules/chessboard.h"
#include <chrono>
#include <atomic>

class ThinkingWriter
{
public:
  ThinkingWriter();

  virtual ~ThinkingWriter() = 0;

  virtual void output(const ChessBoard& board,
                      const SearchResult& result,
                      const std::chrono::milliseconds& time,
                      int depth) = 0;

  void post(bool value);

  bool post() const;

private:
  std::atomic<bool> m_post;
};

#endif // THINKINGWRITER_H
