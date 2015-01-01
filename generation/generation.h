#ifndef GENERATION_H
#define GENERATION_H

#include <cstdint>
#include <string>

#include "olaf/status.h"

namespace olaf
{
namespace generation
{
Status generate_magic(const std::string& output_file, bool verbose);
} // namespace generation
} // namespace olaf

#endif // GENERATION_H
