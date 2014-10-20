#include "olaf/search/nothinkingwriter.h"

namespace olaf
{

void NoThinkingWriter::output(const ChessBoard& /* board */,
                              const SearchResult& /* result */,
                              const std::chrono::milliseconds& /* time */,
                              const int /* depth */)
{}

} // namespace olaf
