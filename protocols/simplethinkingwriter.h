#ifndef SIMPLETHINKINGWRITER_H
#define SIMPLETHINKINGWRITER_H

#include "protocolwriter.h"
#include "olaf/thinkingwriter.h"
#include "olaf/searchresult.h"
#include "olaf/chessboard.h"
#include <chrono>
#include <memory>

namespace olaf
{

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
  explicit SimpleThinkingWriter(ProtocolWriter* writer);

  void output(const ChessBoard &board,
              const SearchResult &result,
              const std::chrono::milliseconds &time,
              int depth);

private:
  ProtocolWriter* const m_writer;

};

} // namespace olaf

#endif // SIMPLETHINKINGWRITER_H
