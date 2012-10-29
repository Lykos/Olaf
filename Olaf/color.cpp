#include "color.h"
#include <cstdint>

using namespace std;

Color next(Color color)
{
  return static_cast<Color>(1 - static_cast<uint_fast8_t>(color));
}
