#include "lrucachetest.h"

#include <string>

#include "olaf/transposition_table/lrucache.h"
#include "testutil.h"

using namespace std;
using namespace testing;

namespace olaf
{
namespace test
{

void LruCacheTest::test_get_set()
{
  LruCache<string> cache(5);

  QASSERT_THAT(cache.get(3), IsNull());
  cache.put(3, "asdaf");
  QASSERT_THAT(cache.get(3), Pointee(Eq("asdaf")));
  cache.put(5, "lol");
  QASSERT_THAT(cache.get(5), Pointee(Eq("lol")));
  QASSERT_THAT(cache.get(3), Pointee(Eq("asdaf")));
  cache.put(3, "ohgott");
  QASSERT_THAT(cache.get(3), Pointee(Eq("ohgott")));
  QASSERT_THAT(cache.get(5), Pointee(Eq("lol")));
  cache.put(8, "lalila");
  QASSERT_THAT(cache.get(8), Pointee(Eq("lalila")));
  QASSERT_THAT(cache.get(5), Pointee(Eq("lol")));
  QASSERT_THAT(cache.get(3), IsNull());
}

} // namespace test
} // namespace olaf
