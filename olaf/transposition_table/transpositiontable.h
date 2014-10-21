#ifndef TRANSPOSITIONTABLEENTRY_H
#define TRANSPOSITIONTABLEENTRY_H

#include <memory>

#include "olaf/transposition_table/lrucache.h"
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
  int depth;
  int score;
  NodeType node_type;
  bool has_best_move;
  Move best_move;
};

extern template class LruCache<TranspositionTableEntry>;

typedef LruCache<TranspositionTableEntry> TranspositionTable;

} // namespace olaf

#endif // TRANSPOSITIONTABLEENTRY_H
