#include "olaf/search/searchcontext.h"
#include <limits>

using namespace std;

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

const TranspositionTableEntry* SearchContext::get() const
{
  if (transposition_table) {
    return transposition_table->get(board.zobrist_hash());
  } else {
    return nullptr;
  }
}

void SearchContext::put(const TranspositionTableEntry& entry)
{
  if (transposition_table) {
    transposition_table->put(board.zobrist_hash(), entry);
  }
}

void SearchContext::put(TranspositionTableEntry&& entry)
{
  if (transposition_table) {
    transposition_table->put(board.zobrist_hash(), move(entry));
  }
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

} // namespace olaf
