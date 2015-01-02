#include "openingbooktest.h"

#include "olaf/opening_book/openingbook.h"
#include "test/testutil.h"

using namespace std;
using namespace testing;

namespace olaf
{
namespace test
{

void OpeningBookTest::test_opening_zobrist_hash_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<qulonglong>("hash");

  QTest::newRow("starting position")
      << parse_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") << 0x463b96181691fc9cull;
    QTest::newRow("position after e2e4")
      << parse_fen("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1") << 0x823c9b50fd114196ull;
  QTest::newRow("position after e2e4 d75")
      << parse_fen("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 2") << 0x0756b94461c50fb0ull;
  QTest::newRow("position after e2e4 d7d5 e4e5")
      << parse_fen("rnbqkbnr/ppp1pppp/8/3pP3/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2") << 0x662fafb965db29d4ull;
  QTest::newRow("position after e2e4 d7d5 e4e5 f7f5")
      << parse_fen("rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3") << 0x22a48b5a8e47ff78ull;
  QTest::newRow("position after e2e4 d7d5 e4e5 f7f5 e1e2")
      << parse_fen("rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPPKPPP/RNBQ1BNR b kq - 0 3") << 0x652a607ca3f242c1ull;
  QTest::newRow("position after e2e4 d7d5 e4e5 f7f5 e1e2 e8f7")
      << parse_fen("rnbq1bnr/ppp1pkpp/8/3pPp2/8/8/PPPPKPPP/RNBQ1BNR w - - 0 4") << 0x00fdd303c946bdd9ull;
  QTest::newRow("position after a2a4 b7b5 h2h4 b5b4 c2c4")
      << parse_fen("rnbqkbnr/p1pppppp/8/8/PpP4P/8/1P1PPPP1/RNBQKBNR b KQkq c3 0 3") << 0x3c8123ea7b067637ull;
  QTest::newRow("position after a2a4 b7b5 h2h4 b5b4 c2c4 b4c3 a1a3")
      << parse_fen("rnbqkbnr/p1pppppp/8/8/P6P/R1p5/1P1PPPP1/1NBQKBNR b Kkq - 0 4") << 0x5c3f9b829b279560ull;
}

void OpeningBookTest::test_opening_zobrist_hash()
{
  QFETCH(ChessBoard, board);
  QFETCH(qulonglong, hash);
  QASSERT_THAT(OpeningBook::opening_zobrist_hash(board), Eq(hash));
}

} // namespace test
} // namespace olaf

