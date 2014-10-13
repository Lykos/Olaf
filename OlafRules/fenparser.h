#ifndef FENPARSER_H
#define FENPARSER_H

#include <string>

#include "chessboard.h"

class FenParser
{
public:
  static bool parse(const std::string& fen, ChessBoard* board);

  static std::string serialize(const ChessBoard& board);

  FenParser() = delete;
};

#endif // FENPARSER_H
