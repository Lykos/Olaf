#include "olaf/search/nothinkingwriter.h"

#include "olaf/search/searcher.h"

namespace olaf
{

void NoThinkingWriter::output(const ChessBoard& /* board */,
                              const SearchResult& /* result */,
                              const int /* nodes */,
                              const std::chrono::milliseconds& /* time */,
                              const Searcher::depth_t /* depth */)
{}

} // namespace olaf
