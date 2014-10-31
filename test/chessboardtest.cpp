#include "test/chessboardtest.h"

#include "olaf/rules/chessboard.h"
#include "olaf/rules/movechecker.h"
#include "olaf/rules/bitboard.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/undoinfo.h"
#include "test/testutil.h"

namespace olaf
{
namespace test
{

void ChessBoardTest::test_friends()
{
  ChessBoard board = create_empty_board();
  board.add_piece(board.turn_color(), PieceSet::c_bishop_index, Position("e5"));
  board.add_piece(board.noturn_color(), PieceSet::c_bishop_index, Position("c3"));
  BitBoard result(Position("e5"));
  QCOMPARE(result, board.friends());
}

void ChessBoardTest::test_opponents()
{
  ChessBoard board = create_empty_board();
  board.add_piece(board.turn_color(), PieceSet::c_bishop_index, Position("e5"));
  board.add_piece(board.noturn_color(), PieceSet::c_bishop_index, Position("f3"));
  BitBoard result(Position("f3"));
  QCOMPARE(result, board.opponents());
}

void ChessBoardTest::test_occupied()
{
  ChessBoard board = create_empty_board();
  board.add_piece(board.turn_color(), PieceSet::c_bishop_index, Position("e5"));
  board.add_piece(board.noturn_color(), PieceSet::c_bishop_index, Position("f3"));
  BitBoard result(0);
  result.set(Position("e5"), true);
  result.set(Position("f3"), true);
  QCOMPARE(result, board.occupied());
}

void ChessBoardTest::test_finished_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<bool>("white_won");
  QTest::addColumn<bool>("black_won");
  QTest::addColumn<bool>("draw");

  QTest::newRow("empty") << create_empty_board() << true << true << false;
  QTest::newRow("initial") << create_initial_board() << false << false << false;
  QTest::newRow("normal position") << parse_fen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -") << false << false << false;
  QTest::newRow("50 moves") << parse_fen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 50 50") << false << false << true;
  QTest::newRow("white won") << parse_fen("r6r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w - -") << true << false << false;
  QTest::newRow("black won") << parse_fen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R6R w - -") << false << true << false;
  {
    ChessBoard repetition_board = parse_fen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w - -");
    UndoInfo dummy;
#ifndef NDEBUG
    const ZobristHash::hash_t hash0 = repetition_board.zobrist_hash();
#endif
    const Move move_white_1 = MoveChecker::complete(Position("a1"), Position("b1"), repetition_board);
    move_white_1.execute(&repetition_board, &dummy);
#ifndef NDEBUG
    const ZobristHash::hash_t hash1 = repetition_board.zobrist_hash();
#endif
    const Move move_black_1 = MoveChecker::complete(Position("a8"), Position("b8"), repetition_board);
    move_black_1.execute(&repetition_board, &dummy);
#ifndef NDEBUG
    const ZobristHash::hash_t hash2 = repetition_board.zobrist_hash();
#endif
    const Move move_white_2 = MoveChecker::complete(Position("b1"), Position("a1"), repetition_board);
    move_white_2.execute(&repetition_board, &dummy);
#ifndef NDEBUG
    const ZobristHash::hash_t hash3 = repetition_board.zobrist_hash();
#endif
    const Move move_black_2 = MoveChecker::complete(Position("b8"), Position("a8"), repetition_board);
    move_black_2.execute(&repetition_board, &dummy);
    assert(hash0 == repetition_board.zobrist_hash());
    move_white_1.execute(&repetition_board, &dummy);
    assert(hash1 == repetition_board.zobrist_hash());
    move_black_1.execute(&repetition_board, &dummy);
    assert(hash2 == repetition_board.zobrist_hash());
    move_white_2.execute(&repetition_board, &dummy);
    assert(hash3 == repetition_board.zobrist_hash());
    move_black_2.execute(&repetition_board, &dummy);
    assert(hash0 == repetition_board.zobrist_hash());
    move_white_1.execute(&repetition_board, &dummy);
    assert(hash1 == repetition_board.zobrist_hash());
    repetition_board.draw();
    QTest::newRow("repetition") << repetition_board << false << false << true;
  }
}

void ChessBoardTest::test_finished()
{
  QFETCH(ChessBoard, board);
  QFETCH(bool, white_won);
  QFETCH(bool, black_won);
  QFETCH(bool, draw);

  QCOMPARE(board.won(Color::White), white_won);
  QCOMPARE(board.won(Color::Black), black_won);
  QCOMPARE(board.draw(), draw);
  QCOMPARE(board.finished(), white_won || black_won || draw);
}

} // namespace test
} // namespace olaf
