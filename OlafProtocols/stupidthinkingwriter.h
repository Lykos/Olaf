#ifndef STUPIDTHINKINGWRITER_H
#define STUPIDTHINKINGWRITER_H

#include "protocolwriter.h"
#include "OlafSearching/thinkingwriter.h"
#include "OlafSearching/searchresult.h"
#include "OlafRules/chessboard.h"
#include <chrono>
#include <memory>

class StupidThinkingWriter : public ThinkingWriter
{
public:
  StupidThinkingWriter(const std::shared_ptr<ProtocolWriter> &writer);

  void output(const ChessBoard &board, const SearchResult &result, const std::chrono::milliseconds &time, int depth);

private:
  std::shared_ptr<ProtocolWriter> m_writer;

};

#endif // STUPIDTHINKINGWRITER_H
