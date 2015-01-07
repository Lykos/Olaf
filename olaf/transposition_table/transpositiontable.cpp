#include "olaf/transposition_table/transpositiontable.h"

#include "olaf/evaluation/positionevaluator.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/undoinfo.h"

using namespace std;

namespace olaf
{

PositionEvaluator::score_t c_margin = 1000;

template class LruCache<SearchResult>;

static SearchResult::score_t score_at_current(const SearchResult::score_t score,
                                              const SearchResult::depth_t distance_to_root)
{
  if (abs(score) >= PositionEvaluator::c_win_score - c_margin) {
    assert(abs(score) + distance_to_root <= PositionEvaluator::c_win_score);
    // If we look at the score from the current position and not from the root, the score
    // gets better by distance_to_root.
    return score < 0 ? score - distance_to_root : score + distance_to_root;
  }
  return score;
}

static SearchResult::score_t score_at_root(const SearchResult::score_t score,
                                           const SearchResult::depth_t distance_to_root)
{
  if (abs(score) >= PositionEvaluator::c_win_score - c_margin) {
    assert(abs(score) - distance_to_root >= PositionEvaluator::c_win_score - c_margin);
    // If we look at the score from the root and not from the current position, the score
    // gets worse by distance_to_root.
    return score < 0 ? score + distance_to_root : score - distance_to_root;
  }
  return score;
}

TranspositionTable::TranspositionTable(const long capacity_bytes):
  m_table(capacity_bytes)
{}

vector<Move> TranspositionTable::reconstruct_pv(ChessBoard* const board) const
{
  vector<UndoInfo> undo_infos;
  vector<Move> pv;
  SearchResult result;
  SearchResult::depth_t distance_to_root = 0;
  while (get(board->zobrist_hash(), distance_to_root, &result)) {
    if (!result.has_best_move) {
      break;
    }
    const Move move = result.best_move;
    undo_infos.emplace_back();
    pv.emplace_back(move);
    move.execute(board, &(undo_infos.back()));
    ++distance_to_root;
  }
  auto move_it = pv.crbegin();
  auto undo_it = undo_infos.crbegin();
  while (move_it != pv.crend() && undo_it != undo_infos.crend()) {
    move_it->undo(*undo_it, board);
    ++move_it;
    ++undo_it;
  }
  assert(move_it == pv.crend() && undo_it == undo_infos.crend());
  return pv;
}

bool TranspositionTable::get(const key_t key,
                             const SearchResult::depth_t distance_to_root,
                             SearchResult* const value) const
{
  const SearchResult* const result = m_table.get(key);
  if (!result) {
    return false;
  }
  *value = *result;
  value->score = score_at_root(value->score, distance_to_root);
  return true;
}

void TranspositionTable::put(const key_t key,
                             const SearchResult::depth_t distance_to_root,
                             const SearchResult& value)
{
  SearchResult adjusted_value = value;
  put(key, distance_to_root, std::move(adjusted_value));
}

void TranspositionTable::put(const key_t key,
                             const SearchResult::depth_t distance_to_root,
                             SearchResult&& value)
{
  value.score = score_at_current(value.score, distance_to_root);
  m_table.put(key, std::move(value));
}

} // namespace olaf
