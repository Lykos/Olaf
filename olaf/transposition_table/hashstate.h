#ifndef HASHSTATE_H
#define HASHSTATE_H

#include <ostream>

namespace olaf
{

struct HashState
{
  typedef std::uint64_t hash_t;

  hash_t zobrist_hash = 0;

  hash_t pawn_zobrist_hash = 0;
};

std::ostream& operator <<(std::ostream& out, const HashState& state);

bool operator ==(const HashState& left, const HashState& right);

} // namespace olaf

#endif // HASHSTATE_H
