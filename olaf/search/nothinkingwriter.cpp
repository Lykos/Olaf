#include "olaf/search/nothinkingwriter.h"

#include "olaf/search/searcher.h"

namespace olaf
{

void NoThinkingWriter::output(const ChessBoard& /* board */,
                              const SearchResult& /* result */,
                              const std::vector<Move>& /* main_variation */,
                              const int /* nodes */,
                              const std::chrono::milliseconds& /* time */,
                              const Searcher::depth_t /* depth */)
{}

} // namespace olaf
