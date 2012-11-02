#include "searchresult.h"

using namespace std;

SearchResult::SearchResult(unsigned int nodes, int value, const vector<Move>& main_variation):
  m_nodes (nodes),
  m_value (value),
  m_main_variation (main_variation)
{}

unsigned int SearchResult::nodes() const
{
  return m_nodes;
}

int SearchResult::value() const
{
  return m_value;
}

const vector<Move>& SearchResult::main_variation() const
{
  return m_main_variation;
}

void SearchResult::add_move(const Move &move)
{
  m_main_variation.push_back(move);
}
