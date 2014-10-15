#ifndef SIMPLEMOVEGENERATOR_H
#define SIMPLEMOVEGENERATOR_H

#include "movegenerator.h"
#include "movecreator.h"
#include "OlafRules/move.h"
#include "OlafRules/chessboard.h"
#include "OlafRules/piece.h"
#include <vector>
#include <memory>

class SimpleMoveGenerator : public MoveGenerator
{
public:
  SimpleMoveGenerator(std::unique_ptr<MoveCreator> creator);

  std::vector<Move> generate_moves(const ChessBoard& board) override;

  std::vector<Move> generate_valid_moves(const ChessBoard& board) override;

private:
  bool valid_move(const ChessBoard& board, const Move& move);

  std::unique_ptr<MoveCreator> m_creator;
};

#endif // SIMPLEMOVEGENERATOR_H
