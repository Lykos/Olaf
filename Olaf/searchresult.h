#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include "move.h"

class SearchResult
{
public:
  SearchResult(unsigned int nodes, const Move& best_move);

  unsigned int nodes() const;

  unsigned int best_move() const;

private:
  unsigned int m_nodes;

  Move m_best_move;

};

#endif // SEARCHRESULT_H
