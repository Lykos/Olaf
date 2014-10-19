#ifndef NOTHINKINGWRITER_H
#define NOTHINKINGWRITER_H

#include "olaf/search/thinkingwriter.h"

namespace olaf
{

class NoThinkingWriter : public ThinkingWriter
{
public:
  void output(const ChessBoard& board,
              const SearchResult& result,
              const std::chrono::milliseconds& time,
              int depth) override;
};

} // namespace olaf

#endif // NOTHINKINGWRITER_H
