#include "hashstate.h"

using namespace std;

namespace olaf
{

std::ostream& operator <<(std::ostream& out, const HashState& state)
{
  return out << "Zobrist hash: " << state.zobrist_hash << endl
             << "Pawn Zobrist hash: " << state.pawn_zobrist_hash;
}

bool operator ==(const HashState& left, const HashState& right)
{
  return left.zobrist_hash == right.zobrist_hash
      && left.pawn_zobrist_hash == right.pawn_zobrist_hash;
}

} // namespace olaf
