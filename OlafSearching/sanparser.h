#ifndef SANPARSER_H
#define SANPARSER_H

#include <memory>
#include <string>
#include "movegenerator.h"

class Move;

class SanParser
{
public:
  SanParser(std::unique_ptr<MoveGenerator> generator);

  bool parse(const std::string& san_move,
             const ChessBoard& board,
             Move* move) const;

private:
  std::unique_ptr<MoveGenerator> m_generator;
};

#endif // SANPARSER_
