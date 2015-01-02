#include "egbbprobertest.h"

#include <gflags/gflags.h>

#include "test/testutil.h"
#include "olaf/tablebases/egbbprober.h"

using namespace std;
using namespace testing;

DECLARE_string(egbb_shared_library);

namespace olaf
{
namespace test
{

const int c_cache_size(1 << 20);

void EgbbProberTest::test_no_so()
{
  EgbbProber prober(c_cache_size);
  const string old_value = FLAGS_egbb_shared_library;
  FLAGS_egbb_shared_library = "invalidnonexisting";
  QVERIFY(!prober.load("").ok());
  FLAGS_egbb_shared_library = old_value;
}

void EgbbProberTest::test_wrong_so()
{
  EgbbProber prober(c_cache_size);
  const string old_value = FLAGS_egbb_shared_library;
  FLAGS_egbb_shared_library = "libolaf.so";
  QVERIFY(!prober.load("").ok());
  FLAGS_egbb_shared_library = old_value;
}

void EgbbProberTest::test_probe_without_load()
{
  EgbbProber prober(c_cache_size);
  const ChessBoard& board = parse_fen("8/6p1/2K2R2/8/8/8/6k1/8 w - - 0 1");
  int score;
  prober.probe(board, &score);
}

void EgbbProberTest::test_probe_for_unknown()
{
  EgbbProber prober(c_cache_size);
  prober.load("/home/bernhard/endgames/egbb4men/");
  const ChessBoard& board = create_initial_board();
  int score;
  QVERIFY(!prober.probe(board, &score));
}

void EgbbProberTest::test_probe_draw()
{
  EgbbProber prober(c_cache_size);
  if (prober.load("/home/bernhard/endgames/egbb4men/").ok()) {
    const ChessBoard& board = parse_fen("8/6p1/2K2R2/8/8/8/6k1/8 b - - 0 1");
    int score = 0;
    QVERIFY(prober.probe(board, &score));
    QASSERT_THAT(score, Eq(0));
  }
}

void EgbbProberTest::test_probe_win()
{
  EgbbProber prober(c_cache_size);
  if (prober.load("/home/bernhard/endgames/egbb4men/").ok()) {
    const ChessBoard& board = parse_fen("8/6p1/2K2R2/8/8/8/6k1/8 w - - 0 1");
    int score = 0;
    QVERIFY(prober.probe(board, &score));
    QASSERT_THAT(score, Gt(500));
  }
}

} // namespace test
} // namespace olaf

