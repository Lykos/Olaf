#include "simplemovecreator.h"
#include "OlafRules/pawn.h"
#include "OlafRules/pieceset.h"

using namespace std;

bool SimpleMoveCreator::valid_move(const ChessBoard &board, const Position &source, const Position &destination)
{
  return board.friendd(source) && board.turn_board().piece(source)->can_move(source, destination, board);
}

bool SimpleMoveCreator::valid_move(const ChessBoard &board, const Position &source, const Position &destination, Piece::piece_index_t conversion)
{
  const shared_ptr<const Pawn> &pawn = PieceSet::instance().pawn();
  return board.friendd(source) && board.turn_board().piece(source) == pawn && pawn->can_move(source, destination, board, conversion);
}

Move SimpleMoveCreator::create_move(const ChessBoard &board, const Position &source, const Position &destination)
{
  return board.turn_board().piece(source)->move(source, destination, board);
}

Move SimpleMoveCreator::create_move(const ChessBoard &board, const Position &source, const Position &destination, Piece::piece_index_t conversion)
{
  const shared_ptr<const Pawn> &pawn = PieceSet::instance().pawn();
  return pawn->move(source, destination, board, conversion);
}
