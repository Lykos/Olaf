#ifndef PAWNTABLE_H
#define PAWNTABLE_H

#include "olaf/transposition_table/lrucache.h"
#include "olaf/search/searchresult.h"

namespace olaf
{

struct PawnTableEntry
{
  SearchResult::score_t score;
  /**
   * @brief major_piece_score will be added only if major opponent pieces are present.
   */
  SearchResult::score_t major_piece_score_white;
  SearchResult::score_t major_piece_score_black;
  BitBoard open_files;
  BitBoard white_halfopen_files;
  BitBoard black_halfopen_files;
  BitBoard behind_passers;
  BitBoard white_trapped_bishops;
  BitBoard black_trapped_bishops;
  BitBoard white_pawn_shield;
  BitBoard black_pawn_shield;
  BitBoard white_pawn_storm;
  BitBoard black_pawn_storm;
};

extern template class LruCache<PawnTableEntry>;

typedef LruCache<PawnTableEntry> PawnTable;

} // namespace olaf

#endif // PAWNTABLE_H
