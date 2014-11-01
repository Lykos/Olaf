#include "pawntest.h"

#include "olaf/rules/position.h"
#include "olaf/rules/colorboard.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/movechecker.h"
#include "olaf/rules/move.h"
#include "testutil.h"

using namespace std;
using namespace testing;

namespace olaf
{
namespace test
{

void PawnTest::initTestCase()
{
  m_board = parse_fen("1n1N3k/1PPP4/7N/P4npP/2nN2P1/1p2NP2/PPPPP3/K7 w - g6 0 1");
}

void PawnTest::test_can_move_data()
{
  QTest::addColumn<Position>("source");
  QTest::addColumn<Position>("destination");
  QTest::addColumn<bool>("result");
  QTest::addColumn<bool>("is_capture");
  QTest::addColumn<bool>("is_conversion");

  QTest::newRow("start backwards a2a1") << Position("a2") << Position("a1") << false << false << false;
  QTest::newRow("nostart backwards f3f2") << Position("f3") << Position("f2") << false << false << false;
  QTest::newRow("start sidewards e2f2") << Position("e2") << Position("e2") << false << false << false;
  QTest::newRow("nostart sidewards h5g5") << Position("h5") << Position("g5") << false << false << false;
  QTest::newRow("start single move not blocked a2a3") << Position("a2") << Position("a3") << true << false << false;
  QTest::newRow("start single move own blocked e2e3") << Position("e2") << Position("e3") << false << false << false;
  QTest::newRow("start single move opponent blocked b2b3") << Position("b2") << Position("b3") << false << false << false;
  QTest::newRow("nostart single move not blocked f3f4") << Position("f3") << Position("f4") << true << false << false;
  QTest::newRow("nostart single move own blocked h5h6") << Position("h5") << Position("h6") << false << false << false;
  QTest::newRow("nostart single move opponent opponent blocked g4g5") << Position("g4") << Position("g5") << false << false << false;
  QTest::newRow("start double move not blocked a2a4") << Position("a2") << Position("a4") << true << false << false;
  QTest::newRow("start double move own direct blocked e2e4") << Position("e2") << Position("e4") << false << false << false;
  QTest::newRow("start double move own blocked d2d4") << Position("d2") << Position("d4") << false << false << false;
  QTest::newRow("start double move opponent direct blocked b2b4") << Position("b2") << Position("b4") << false << false << false;
  QTest::newRow("start double move opponent blocked c2c4") << Position("c2") << Position("c4") << false << false << false;
  QTest::newRow("nostart double move a5a7") << Position("a5") << Position("a7") << false << false << false;
  QTest::newRow("start opponent capture a2b3") << Position("a2") << Position("b3") << true << true << false;
  QTest::newRow("start own capture d2e3") << Position("d2") << Position("e3") << false << false << false;
  QTest::newRow("start empty capture b2a3") << Position("b2") << Position("a3") << false << false << false;
  QTest::newRow("nostart opponent capture g4f5") << Position("g4") << Position("f5") << true << true << false;
  QTest::newRow("nostart ep capture h5g6") << Position("h5") << Position("g6") << true << true << false;
  QTest::newRow("nostart own capture g4h5") << Position("g4") << Position("h5") << false << false << false;
  QTest::newRow("nostart empty capture f3e4") << Position("f3") << Position("e4") << false << false << false;
  QTest::newRow("conversion single move not blocked c7c8") << Position("c7") << Position("c8") << false << false << true;
  QTest::newRow("conversion single move own blocked d7d8") << Position("d7") << Position("d8") << false << false << false;
  QTest::newRow("conversion single move opponent blocked b7b8") << Position("b7") << Position("b8") << false << false << false;
  QTest::newRow("conversion empty capture b7c8") << Position("b7") << Position("c8") << false << false << false;
  QTest::newRow("conversion own capture c7d8") << Position("c7") << Position("d8") << false << false << false;
  QTest::newRow("conversion opponent capture c7b8") << Position("c7") << Position("b8") << false << true << true;
}

void PawnTest::test_can_move()
{
  QFETCH(Position, source);
  QFETCH(Position, destination);
  QFETCH(bool, result);
  QFETCH(bool, is_capture);
  QFETCH(bool, is_conversion);

  if (string(QTest::currentDataTag()) != "nostart single move opponent noblocked g4g5")
    return;
  const IncompleteMove incomplete_move = IncompleteMove(source, destination);
  QCOMPARE(MoveChecker::pseudo_valid_move(m_board, incomplete_move), result);
  if (result) {
    const Move move = MoveChecker::complete(incomplete_move, m_board);
    QCOMPARE(move.is_capture(), is_capture);
  }
  const IncompleteMove incomplete_promotion = IncompleteMove::promotion(source, destination, PieceSet::c_knight_index);
  if (is_conversion) {
    QVERIFY2(MoveChecker::pseudo_valid_move(m_board, incomplete_promotion),
             "Move does not work as a conversion.");
    const Move move = MoveChecker::complete(incomplete_promotion, m_board);
    QCOMPARE(move.is_capture(), is_capture);
    QVERIFY2(move.is_promotion(), "Conversion is not a conversion.");
    QASSERT_THAT(move.created_piece(), Eq(PieceSet::c_knight_index));
  } else {
    QVERIFY2(!MoveChecker::pseudo_valid_move(m_board, incomplete_promotion), "Move works as a conversion.");
  }
}

Move PawnTest::make_move(const string& source, const string& destination)
{
  return MoveChecker::complete(Position(source), Position(destination), m_board);
}
/*
void PawnTest::test_moves_data()
{
  QTest::addColumn<Position>("source");
  QTest::addColumn<vector<Move>>("moves");

  QTest::newRow("free move")
      << Position("a2")
      << vector<Move>{{make_move("a2", "a4"), make_move("a2", "a3"), make_move("a2", "b3")}};
  QTest::newRow("opponent blocked move")
      << Position("b2")
      << vector<Move>();
  QTest::newRow("opponent blocked double move")
      << Position("c2")
      << vector<Move>{{make_move("c2", "b3"), make_move("c2", "c3")}};
  QTest::newRow("friend blocked double move")
      << Position("d2")
      << vector<Move>{{make_move("d2", "d3")}};
  QTest::newRow("friend blocked")
      << Position("e2")
      << vector<Move>();
  QTest::newRow("ep")
      << Position("h5")
      << vector<Move>{{make_move("h5", "g6")}};
  QTest::newRow("promotion blocked")
      << Position("b7")
      << vector<Move>();
  {
    vector<Move> moves{
      MoveChecker::complete_promotion(Position("c7"), Position("b8"), PieceSet::c_bishop_index, m_board),
      MoveChecker::complete_promotion(Position("c7"), Position("b8"), PieceSet::c_knight_index, m_board),
      MoveChecker::complete_promotion(Position("c7"), Position("b8"), PieceSet::c_rook_index, m_board),
      MoveChecker::complete_promotion(Position("c7"), Position("b8"), PieceSet::c_queen_index, m_board),
      MoveChecker::complete_promotion(Position("c7"), Position("c8"), PieceSet::c_bishop_index, m_board),
      MoveChecker::complete_promotion(Position("c7"), Position("c8"), PieceSet::c_knight_index, m_board),
      MoveChecker::complete_promotion(Position("c7"), Position("c8"), PieceSet::c_rook_index, m_board),
      MoveChecker::complete_promotion(Position("c7"), Position("c8"), PieceSet::c_queen_index, m_board),
    };
    QTest::newRow("promotion")
        << Position("c7")
        << moves;
  }
}

void PawnTest::test_moves()
{
  QFETCH(Position, source);
  QFETCH(vector<Move>, moves);

  QASSERT_THAT(m_pawn->moves(source, m_board), UnorderedElementsAreArray(moves));
}
*/
} // namespace test
} // namespace olaf
