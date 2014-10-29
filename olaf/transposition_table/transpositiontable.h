#ifndef TRANSPOSITIONTABLEENTRY_H
#define TRANSPOSITIONTABLEENTRY_H

#include <memory>

#include "olaf/transposition_table/lrucache.h"
#include "olaf/evaluation/positionevaluator.h"
#include "olaf/search/searcher.h"
#include "olaf/rules/move.h"

namespace olaf
{

enum class NodeType
{
  PvNode,
  CutNode,
  AllNode
};

struct TranspositionTableEntry
{
  /**
   * @brief depth of the search beyond the current position.
   *        This should be used to determine how valuable a result is.
   */
  Searcher::depth_t depth;

  /**
   * @brief result_depth this is the actual depth of the node for which
   *        this score was returned. This can be more than depth because
   *        of quiescent search. It should only be used for special interior
   *        node detection.
   */
  Searcher::depth_t result_depth;

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
