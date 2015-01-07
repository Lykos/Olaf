#ifndef TRANSPOSITIONTABLEENTRY_H
#define TRANSPOSITIONTABLEENTRY_H

#include <memory>
#include <vector>

#include "olaf/transposition_table/lrucache.h"
#include "olaf/search/searchresult.h"
#include "olaf/rules/move.h"
#include "olaf/search/nodetype.h"

namespace olaf
{

extern template class LruCache<SearchResult>;

class TranspositionTable {
public:
  typedef LruCache<SearchResult>::key_t key_t;

  explicit TranspositionTable(long capacity_bytes);

  std::vector<Move> reconstruct_pv(ChessBoard* const board) const;

  bool get(key_t key, SearchResult::depth_t distance_to_root, SearchResult* value) const;

  void put(key_t key, SearchResult::depth_t distance_to_root, const SearchResult& value);

  void put(key_t key, SearchResult::depth_t distance_to_root, SearchResult&& value);

  inline double hit_rate() const { return m_table.hit_rate(); }

  inline long hits() const { return m_table.hits(); }

  inline long misses() const { return m_table.misses(); }

private:
  LruCache<SearchResult> m_table;
};

} // namespace olaf

#endif // TRANSPOSITIONTABLEENTRY_H
