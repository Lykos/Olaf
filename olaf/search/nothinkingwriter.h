#ifndef NOTHINKINGWRITER_H
#define NOTHINKINGWRITER_H

#include "olaf/search/thinkingwriter.h"
#include "olaf/search/searcher.h"

namespace olaf
{

class ChessBoard;
class SearchResult;

class NoThinkingWriter : public ThinkingWriter
{
public:
  void output(const ChessBoard& board,
              const SearchResult& result,
              int nodes,
              const std::chrono::milliseconds& time,
              Searcher::depth_t depth) override;
};

} // namespace olaf

#endif // NOTHINKINGWRITER_H
