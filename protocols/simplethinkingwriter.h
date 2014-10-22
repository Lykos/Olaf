#ifndef SIMPLETHINKINGWRITER_H
#define SIMPLETHINKINGWRITER_H

#include <chrono>
#include <memory>

#include "olaf/search/thinkingwriter.h"
#include "olaf/search/searcher.h"

namespace olaf
{

class ChessBoard;
class ProtocolWriter;
class SearchResult;

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

  void output(const ChessBoard& board,
              const SearchResult& result,
              const std::chrono::milliseconds &time,
              Searcher::depth_t depth);

private:
  ProtocolWriter* const m_writer;

};

} // namespace olaf

#endif // SIMPLETHINKINGWRITER_H
