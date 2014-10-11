#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include "OlafRules/move.h"
#include <vector>

class SearchResult
{
public:
  SearchResult(unsigned int nodes = 0, int value = 0, const std::vector<Move>& main_variation = std::vector<Move>());

  SearchResult operator-() const;

  bool valid() const;

  unsigned int nodes() const;

  int value() const;

  const std::vector<Move>& main_variation() const;

  void add_move(const Move &move);

private:
  unsigned int m_nodes;

  int m_value;

  std::vector<Move> m_main_variation;

};

#endif // SEARCHRESULT_H
