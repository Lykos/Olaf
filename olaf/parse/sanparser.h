#ifndef SANPARSER_H
#define SANPARSER_H

#include <memory>
#include <string>

#include "olaf/search/movegenerator.h"
#include "olaf/status.h"

namespace olaf
{

class ChessBoard;
class Move;

class SanParser
{
public:
  explicit SanParser(std::unique_ptr<MoveGenerator> generator);

  Status parse(const std::string& san_move,
               const ChessBoard& board,
               Move* move) const;

private:
  std::unique_ptr<MoveGenerator> m_generator;
};

} // namespace olaf

#endif // SANPARSER_H
