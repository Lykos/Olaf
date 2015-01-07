#include "olaf/search/searchcontext.h"

#include <limits>

using namespace std;
using namespace chrono;

namespace olaf
{

SearchContext::SearchContext():
  time_mode(TimeMode::FIXED),
  total_time(0),
  forced_stopper(nullptr),
  weak_stopper(nullptr),
  depth_mode(DepthMode::ITERATIVE),
  prober(nullptr),
  transposition_table(nullptr),
  pawn_table(nullptr)
{}

bool SearchContext::probe(score_t* const score)
{
  if (prober) {
    return prober->probe(board, score);
  } else {
    return false;
  }
}

bool SearchContext::get(const depth_t current_depth, SearchResult* const result) const
{
  if (transposition_table) {
    return transposition_table->get(board.zobrist_hash(), search_depth - current_depth, result);
  } else {
    return false;
  }
}

void SearchContext::put(const depth_t current_depth, const SearchResult& entry)
{
  if (transposition_table) {
    transposition_table->put(board.zobrist_hash(), search_depth - current_depth, entry);
  }
}

void SearchContext::put(const depth_t current_depth, SearchResult&& entry)
{
  if (transposition_table) {
    transposition_table->put(board.zobrist_hash(), search_depth - current_depth, move(entry));
  }
}

vector<Move> SearchContext::reconstruct_pv()
{
  if (transposition_table) {
    return transposition_table->reconstruct_pv(&board);
  }
  return {};
}

const PawnTableEntry* SearchContext::get_pawns() const
{
  if (pawn_table) {
    return pawn_table->get(board.pawn_zobrist_hash());
  } else {
    return nullptr;
  }
}

void SearchContext::put_pawns(const PawnTableEntry& entry)
{
  if (pawn_table) {
    pawn_table->put(board.pawn_zobrist_hash(), entry);
  }
}

void SearchContext::put_pawns(PawnTableEntry&& entry)
{
  if (pawn_table) {
    pawn_table->put(board.pawn_zobrist_hash(), move(entry));
  }
}

milliseconds SearchContext::elapsed() const
{
  return duration_cast<milliseconds>(steady_clock::now() - time_start);
}

} // namespace olaf
