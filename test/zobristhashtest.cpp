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

  const HashState& initial_hash_state = board.hash_state();
  ZobristHash::calculate(board, &(board.hash_state()));
  QASSERT_THAT(board.hash_state(), Eq(initial_hash_state));
  set<ZobristHash::hash_t> hashes{initial_hash_state.zobrist_hash};
  for (Move& move : m_generator->generate_valid_moves(board)) {
    UndoInfo undo_info;
    move.execute(&board, &undo_info);
    const HashState& move_hash_state = board.hash_state();
    QVERIFY(!hashes.count(move_hash_state.zobrist_hash));
    hashes.insert(move_hash_state.zobrist_hash);
    ZobristHash::calculate(board, &(board.hash_state()));
    QASSERT_THAT(board.hash_state(), Eq(move_hash_state));
    move.undo(undo_info, &board);
    const HashState& undo_hash_state = board.hash_state();
    ZobristHash::calculate(board, &(board.hash_state()));
    QASSERT_THAT(board.hash_state(), Eq(undo_hash_state));
    QASSERT_THAT(undo_hash_state, Eq(initial_hash_state));
  }
}

} // namespace test
} // namespace olaf
