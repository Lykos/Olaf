#include "zobristhashtest.h"

#include <memory>
#include <set>

#include "testutil.h"
#include "olaf/rules/undoinfo.h"
#include "olaf/search/perft.h"
#include "olaf/search/nothinkingwriter.h"
#include "olaf/search/searcherfactory.h"
#include "olaf/transposition_table/zobristhash.h"

using namespace std;
using namespace testing;

namespace olaf
{
namespace test
{

void ZobristHashTest::init_test_case()
{
  m_generator = m_factory_owner.factory.move_generator();
}

void ZobristHashTest::test_calculate_data()
{
  QTest::addColumn<ChessBoard>("board");
  for (const Perft::PerftExample& example : Perft::examples()) {
    QTest::newRow(example.name.c_str()) << parse_fen(example.fen);
  }
}

void ZobristHashTest::test_calculate()
{
  QFETCH(ChessBoard, board);

  const ZobristHash::hash_t hash = board.zobrist_hash();
  ZobristHash::calculate(&board);
  QASSERT_THAT(board.zobrist_hash(), Eq(hash));
  set<ZobristHash::hash_t> hashes{hash};
  for (Move& move : m_generator->generate_valid_moves(board)) {
    UndoInfo undo_info;
    move.execute(&board, &undo_info);
    const ZobristHash::hash_t move_hash = board.zobrist_hash();
    QVERIFY(!hashes.count(move_hash));
    hashes.insert(move_hash);
    ZobristHash::calculate(&board);
    QASSERT_THAT(board.zobrist_hash(), Eq(move_hash));
    move.undo(undo_info, &board);
    const ZobristHash::hash_t undo_hash = board.zobrist_hash();
    ZobristHash::calculate(&board);
    QASSERT_THAT(board.zobrist_hash(), Eq(undo_hash));
    QASSERT_THAT(undo_hash, Eq(hash));
  }
}

} // namespace test
} // namespace olaf
