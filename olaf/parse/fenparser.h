#ifndef FENPARSER_H
#define FENPARSER_H

#include <string>

#include "olaf/status.h"

namespace olaf
{

class ChessBoard;

class FenParser
{
public:
  /**
   * @brief parse parses a FEN code and sets up the position.
   * @param fen a string starting with a FEN code.
   * @param board if parsed successfully, this board will contain the described position.
   * @param end_position if provided, this will be set to the end of the parsed FEN in the string.
   * @return Status::valid() if everything is ok, otherwise Status::error(a descriptive error mesage).
   */
  static Status parse(const std::string& fen, ChessBoard* board, int* end_position = nullptr);

  static std::string serialize(const ChessBoard& board);

  FenParser() = delete;
};

} // namespace olaf

#endif // FENPARSER_H
