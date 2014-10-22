#ifndef TRANSPOSITIONTABLEENTRY_H
#define TRANSPOSITIONTABLEENTRY_H

#include <memory>

#include "olaf/transposition_table/lrucache.h"
#include "olaf/evaluation/positionevaluator.h"
#include "olaf/search/searcher.h"
#include "olaf/rules/position.h"
#include "olaf/rules/piece.h"
#include "olaf/rules/move.h"

namespace olaf
{

class Move;

enum class NodeType
{
  PvNode,
  CutNode,
  AllNode
};

struct TranspositionTableEntry
{
  Searcher::depth_t depth;
  PositionEvaluator::score_t score;
  NodeType node_type;
  Move best_move;
  bool has_best_move;
  bool terminal;
};

extern template class LruCache<TranspositionTableEntry>;

typedef LruCache<TranspositionTableEntry> TranspositionTable;

} // namespace olaf

#endif // TRANSPOSITIONTABLEENTRY_H
