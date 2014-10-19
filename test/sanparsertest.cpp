#include "sanparsertest.h"

#include <QtTest/QTest>
#include <vector>
#include <iostream>

#include "testutil.h"
#include "olaf/chessboard.h"
#include "olaf/pieceset.h"
#include "olaf/sanparser.h"
#include "olaf/searcherfactory.h"
#include "olaf/nothinkingwriter.h"

using namespace std;

Q_DECLARE_METATYPE(olaf::ChessBoard)
Q_DECLARE_METATYPE(olaf::Move)

namespace olaf
{
namespace test
{

void SanParserTest::initTestCase()
{
  NoThinkingWriter no_thinking_writer;
  SearcherFactory factory(&no_thinking_writer);
  m_parser = factory.san_parser();
}

void SanParserTest::test_parse_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<QString>("san");
  QTest::addColumn<Move>("move");

  QTest::newRow("initial pawnmove") << create_initial_board()
                                    << "e4"
                                    << Move({},
                                            Position("e2"),
                                            Position("e4"),
                                            false,
                                            false,
                                            Piece::c_no_piece);
  ChessBoard board = parse_fen("3k2n1/7P/n1Q2n2/3pP1QQ/2Q1Q1Q1/7p/8/R3K2R w KQ d6 0 1");
  QTest::newRow("pawn capture")
      << board << "exf6" << Move({},
                                 Position("e5"),
                                 Position("f6"),
                                 true,
                                 false,
                                 Piece::c_no_piece);
  QTest::newRow("pawn promotion queen")
      << board << "h8=Q" << Move({},
                                 Position("h7"),
                                 Position("h8"),
                                 false,
                                 true,
                                 PieceSet::instance().queen().piece_index());
  QTest::newRow("pawn promotion rook")
      << board << "h8=R" << Move({},
                                 Position("h7"),
                                 Position("h8"),
                                 false,
                                 true,
                                 PieceSet::instance().rook().piece_index());
  QTest::newRow("pawn promotion bishop")
      << board << "h8=B" << Move({},
                                 Position("h7"),
                                 Position("h8"),
                                 false,
                                 true,
                                 PieceSet::instance().bishop().piece_index());
  QTest::newRow("pawn promotion knight")
      << board << "h8=N" << Move({},
                                 Position("h7"),
                                 Position("h8"),
                                 false,
                                 true,
                                 PieceSet::instance().knight().piece_index());
  QTest::newRow("pawn promotion queen capture")
      << board << "hxg8=Q+" << Move({},
                                    Position("h7"),
                                    Position("g8"),
                                    true,
                                    true,
                                    PieceSet::instance().queen().piece_index());
  QTest::newRow("pawn promotion rook capture")
      << board << "hxg8=R+" << Move({},
                                    Position("h7"),
                                    Position("g8"),
                                    true,
                                    true,
                                    PieceSet::instance().rook().piece_index());
  QTest::newRow("pawn promotion bishop capture")
      << board << "hxg8=B" << Move({},
                                   Position("h7"),
                                   Position("g8"),
                                   true,
                                   true,
                                   PieceSet::instance().bishop().piece_index());
  QTest::newRow("pawn promotion knight capture")
      << board << "hxg8=N" << Move({},
                                   Position("h7"),
                                   Position("g8"),
                                   true,
                                   true,
                                   PieceSet::instance().knight().piece_index());
  QTest::newRow("row disambiguation")
      << board << "Q4a4" << Move({},
                                 Position("c4"),
                                 Position("a4"),
                                 false,
                                 false,
                                 Piece::c_no_piece);
  QTest::newRow("row disambiguation capture")
      << board << "Qgxh3" << Move({},
                                 Position("g4"),
                                 Position("h3"),
                                 true,
                                 false,
                                 Piece::c_no_piece);
  QTest::newRow("column disambiguation")
      << board << "Qcc2" << Move({},
                                 Position("c4"),
                                 Position("c2"),
                                 false,
                                 false,
                                 Piece::c_no_piece);
  QTest::newRow("column disambiguation capture")
      << board << "Q4xa6" << Move({},
                                  Position("c4"),
                                  Position("a6"),
                                  true,
                                  false,
                                  Piece::c_no_piece);
  QTest::newRow("row and column disambiguation")
      << board << "Qg5h4" << Move({},
                                  Position("g5"),
                                  Position("h4"),
                                  false,
                                  false,
                                  Piece::c_no_piece);
  QTest::newRow("row and column disambiguation capture")
      << board << "Qc4xd5" << Move({},
                                   Position("c4"),
                                   Position("d5"),
                                   true,
                                   false,
                                   Piece::c_no_piece);
  QTest::newRow("ep")
      << board << "exd6" << Move({},
                                 Position("e5"),
                                 Position("d6"),
                                 true,
                                 false,
                                 Piece::c_no_piece);
  QTest::newRow("castle q")
      << board << "O-O-O" << Move({},
                                  Position("e1"),
                                  Position("c1"),
                                  false,
                                  false,
                                  Piece::c_no_piece);
  QTest::newRow("castle k")
      << board << "O-O" << Move({},
                                Position("e1"),
                                Position("g1"),
                                false,
                                false,
                                Piece::c_no_piece);
}

void SanParserTest::test_parse()
{
  QFETCH(ChessBoard, board);
  QFETCH(QString, san);
  QFETCH(Move, move);

  Move actual_move;
  QVERIFY(m_parser->parse(san.toStdString(), board, &actual_move));
  QASSERT_THAT(actual_move, IsSameMove(move));

} // namespace test
} // namespace olaf
}
