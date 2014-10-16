#ifndef NOTHINKINGWRITER_H
#define NOTHINKINGWRITER_H

#include "thinkingwriter.h"

class NoThinkingWriter : public ThinkingWriter
{
public:
  void output(const ChessBoard& board,
              const SearchResult& result,
              const std::chrono::milliseconds& time,
              int depth) override;
};

#endif // NOTHINKINGWRITER_H
