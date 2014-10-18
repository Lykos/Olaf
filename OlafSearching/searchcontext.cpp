#include "searchcontext.h"
#include <limits>

using namespace std;

// Note that numeric_limits is asymmetric.
// But for negamax, we need symmetry, so we use
// -max instead of min.

SearchContext::SearchContext():
  time_mode(TimeMode::BOUNDED),
  forced_stopper(nullptr),
  weak_stopper(nullptr),
  depth_mode(DepthMode::ITERATIVE)
{}
