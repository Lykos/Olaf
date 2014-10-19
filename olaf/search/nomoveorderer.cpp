#include "olaf/search/moveorderer.h"

namespace olaf
{

void NoMoveOrderer::order_moves(const ChessBoard& /* board */,
                                std::vector<Move>* /* moves */)
{}

} // namespace olaf
