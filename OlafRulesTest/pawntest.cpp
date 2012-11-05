#include "pawntest.h"
#include "OlafRules/position.h"
#include "OlafRules/pawn.h"
#include "OlafRules/chessboard.h"
#include <memory>

using namespace std;

PawnTest::test_can_move_data()
{

}

PawnTest::test_can_move()
{
  QFETCH(ChessBoard, board);
  QFETCH(Position, source);
  QFETCH(Position, destination);
  QFETCH(bool, result);

  shared_ptr<Pawn> pawn = PieceSet::instance().
}

PawnTest::test_moves_data()
{

}

PawnTest::test_moves()
{

}
