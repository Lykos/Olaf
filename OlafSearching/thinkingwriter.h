#ifndef THINKINGWRITER_H
#define THINKINGWRITER_H

#include "searchresult.h"
#include "OlafRules/chessboard.h"
#include <chrono>

class ThinkingWriter
{
public:
  virtual ~ThinkingWriter() = 0;

  virtual void output(const ChessBoard &board, const SearchResult &result, const std::chrono::milliseconds &time, int depth) = 0;

};

#endif // THINKINGWRITER_H
