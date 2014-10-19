#ifndef SANPARSER_H
#define SANPARSER_H

#include <memory>
#include <string>
#include "movegenerator.h"
#include "movecreator.h"

namespace olaf
{

class Move;

class SanParser
{
public:
  SanParser(std::unique_ptr<MoveGenerator> generator,
            std::unique_ptr<MoveCreator> creator);

  bool parse(const std::string& san_move,
             const ChessBoard& board,
             Move* move) const;

private:
  std::unique_ptr<MoveGenerator> m_generator;
  std::unique_ptr<MoveCreator> m_creator;
};

} // namespace olaf

#endif // SANPARSER_H
