#ifndef PAWNTABLE_H
#define PAWNTABLE_H

#include "olaf/transposition_table/lrucache.h"
#include "olaf/evaluation/positionevaluator.h"

namespace olaf
{

struct PawnTableEntry {
  PositionEvaluator::score_t score;
};

extern template class LruCache<PawnTableEntry>;

typedef LruCache<PawnTableEntry> PawnTable;

} // namespace olaf

#endif // PAWNTABLE_H
