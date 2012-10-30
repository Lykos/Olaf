#include "searchresult.h"


SearchResult::SearchResult(unsigned int nodes, const Move& best_move):
  m_nodes (nodes),
  m_best_move (best_move)
{}

unsigned int SearchResult::nodes() const
{
  return m_nodes;
}

unsigned int SearchResult::best_move() const
{
  return m_best_move;
}
