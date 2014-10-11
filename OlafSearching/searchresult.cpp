#include "searchresult.h"

using namespace std;

SearchResult::SearchResult(unsigned int nodes, int value, const vector<Move>& main_variation):
  m_nodes (nodes),
  m_value (value),
  m_main_variation (main_variation)
{}

SearchResult SearchResult::operator-() const
{
  return SearchResult(m_nodes, -m_value, m_main_variation);
}

bool SearchResult::valid() const
{
  return m_nodes != 0;
}

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
