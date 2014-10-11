#ifndef SIMPLETHINKINGWRITER_H
#define SIMPLETHINKINGWRITER_H

#include "protocolwriter.h"
#include "OlafSearching/thinkingwriter.h"
#include "OlafSearching/searchresult.h"
#include "OlafRules/chessboard.h"
#include <chrono>
#include <memory>

/**
 * @brief The SimpleThinkingWriter class is a very simple class
 *        that creates pondering output.
 */
class SimpleThinkingWriter : public ThinkingWriter
{
 public:
  /**
   * @brief SimpleThinkingWriter does not take ownership of the passed pointer.
   */
  SimpleThinkingWriter(ProtocolWriter* writer);

  void output(const ChessBoard &board,
              const SearchResult &result,
              const std::chrono::milliseconds &time,
              int depth);

private:
  std::shared_ptr<ProtocolWriter> m_writer;

};

#endif // SIMPLETHINKINGWRITER_H
