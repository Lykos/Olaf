#ifndef SANPARSER_H
#define SANPARSER_H

#include <memory>
#include <string>
#include "olaf/search/movegenerator.h"
#include "olaf/rules/movechecker.h"

namespace olaf
{

class Move;

class SanParser
{
public:
  explicit SanParser(std::unique_ptr<MoveGenerator> generator);

  bool parse(const std::string& san_move,
             const ChessBoard& board,
             Move* move) const;

private:
  std::unique_ptr<MoveGenerator> m_generator;
};

} // namespace olaf

#endif // SANPARSER_H
