#include "moveorderertest.h"

#include "olaf/search/moveorderer.h"
#include "olaf/search/searchcontext.h"
#include "olaf/rules/movechecker.h"
#include "testutil.h"

using namespace std;
using namespace testing;

namespace olaf
{
namespace test
{

void MoveOrdererTest::initTestCase()
{
  m_orderer = m_factory_owner.factory.move_orderer();
}

void MoveOrdererTest::test_order_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<bool>("has_hash_move");
  QTest::addColumn<SearchResult>("entry");
  QTest::addColumn<bool>("has_killer_move");
  QTest::addColumn<Move>("killer_move");
  QTest::addColumn<vector<Move>>("moves");
  QTest::addColumn<vector<Move>>("ordered_moves");

  ChessBoard board = parse_fen("rnb1kbnr/ppp1pppp/1q6/3p4/2P1P3/8/PP1P1PPP/RNBQKBNR b KQkq - 0 1");
  const Move quiet_move = MoveChecker::complete(Position("d5"), Position("d4"), board);
  const Move positive_see_move = MoveChecker::complete(Position("d5"), Position("e4"), board);
  const Move neutral_see_move = MoveChecker::complete(Position("d5"), Position("c4"), board);
  const Move negative_see_move = MoveChecker::complete(Position("b6"), Position("b2"), board);
  const Move killer_move = MoveChecker::complete(Position("a7"), Position("a6"), board);
  {
    const Move hash_move = MoveChecker::complete(Position("a7"), Position("a5"), board);
    vector<Move> moves{quiet_move, positive_see_move, negative_see_move, hash_move, neutral_see_move};
    vector<Move> ordered_moves{hash_move, positive_see_move, neutral_see_move, quiet_move, negative_see_move};
    SearchResult transposition_table_result;
    transposition_table_result.has_best_move = true;
    transposition_table_result.best_move = hash_move;
    transposition_table_result.valid = true;
    QTest::newRow("hash move first")
        << board << true << transposition_table_result
        << false << killer_move << moves << ordered_moves;
  }
  {
    vector<Move> moves{quiet_move, positive_see_move, negative_see_move, neutral_see_move};
    vector<Move> ordered_moves{positive_see_move, neutral_see_move, quiet_move, negative_see_move};
    SearchResult transposition_table_result;
    QTest::newRow("no hash move")
        << board << false << transposition_table_result << false << killer_move << moves << ordered_moves;
  }
  {
    vector<Move> moves{quiet_move, positive_see_move, negative_see_move, neutral_see_move, killer_move};
    vector<Move> ordered_moves{positive_see_move, neutral_see_move, killer_move, quiet_move, negative_see_move};
    SearchResult transposition_table_result;
    QTest::newRow("killer move")
        << board << false << transposition_table_result << true << killer_move << moves << ordered_moves;
  }
}

void MoveOrdererTest::test_order()
{
  QFETCH(ChessBoard, board);
  QFETCH(bool, has_hash_move);
  QFETCH(SearchResult, entry);
  QFETCH(bool, has_killer_move);
  QFETCH(Move, killer_move);
  QFETCH(vector<Move>, moves);
  QFETCH(vector<Move>, ordered_moves);

  SearchContext context;
  context.search_depth = 1;
  context.board = board;
  if (has_hash_move) {
    context.put(0, entry);
  }
  if (has_killer_move) {
    context.killers.resize(1);
    context.killers[0][0] = killer_move;
  }
  SearchState state;
  state.depth = 1;

  m_orderer.order_moves(entry, state, &context, &moves);
  QASSERT_THAT(moves, ElementsAreArray(ordered_moves));
}

void MoveOrdererTest::test_see_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<IncompleteMove>("incomplete_move");
  QTest::addColumn<Searcher::score_t>("score");

  QTest::newRow("no capture") << create_initial_board() << IncompleteMove(Position("e2"), Position("e4")) << 0;
  QTest::newRow("simple capture") << parse_fen("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1")
                                  << IncompleteMove(Position("d5"), Position("e4")) << 100;
  QTest::newRow("guarded capture") << parse_fen("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1")
                                   << IncompleteMove(Position("e4"), Position("d5")) << 0;
  QTest::newRow("complex capture") << parse_fen("rnbqkb1r/pp3ppp/2p1pn2/3p3Q/2P1P3/2N5/PP1P1PPP/R1B1KBNR w KQkq - 2 5")
                                   << IncompleteMove(Position("e4"), Position("d5")) << 0;
  QTest::newRow("complex capture win") << parse_fen("rnb1kbnr/ppq2ppp/2p1p3/3p3Q/2P1P3/2N5/PP1P1PPP/R1B1KBNR w KQkq - 2 5")
                                       << IncompleteMove(Position("e4"), Position("d5")) << 100;
  QTest::newRow("xray capture win") << parse_fen("rnbqk1nr/pp2bppp/2p1p3/3p4/2P1P3/2N2Q2/PP1P1PPP/R1B1KBNR w KQkq - 2 5")
                                    << IncompleteMove(Position("e4"), Position("d5")) << 100;
  QTest::newRow("xray through opponent") << parse_fen("rn1qk1nr/pp2bppp/2p1p3/3p4/2P1P3/1bN2Q2/PP1P1PPP/R1B1KBNR w KQkq - 0 1")
                                         << IncompleteMove(Position("e4"), Position("d5")) << 0;
  QTest::newRow("not worth it") << parse_fen("rnbqkbnr/ppp2pp1/3p3p/4p3/5B2/3P1N2/PPP1PPPP/RN1QKB1R w KQkq e6 0 4")
                                << IncompleteMove(Position("f4"), Position("e5")) << -230;
}

void MoveOrdererTest::test_see()
{
  QFETCH(ChessBoard, board);
  QFETCH(IncompleteMove, incomplete_move);
  QFETCH(Searcher::score_t, score);

  const Move move = MoveChecker::complete(incomplete_move, board);
  MoveOrderer::SeeState see_state;
  MoveOrderer::init_see_state(board, &see_state);
  Searcher::score_t actual_score = MoveOrderer::see(board, move, see_state);
  QASSERT_THAT(actual_score, Eq(score));
}

} // namespace test
} // namespace olaf
