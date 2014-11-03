#ifndef TABLEBASEPROBER_H
#define TABLEBASEPROBER_H

#include "olaf/search/searchresult.h"

namespace olaf
{

class ChessBoard;

class TablebaseProber
{
public:
  typedef SearchResult::score_t score_t;

  virtual ~TablebaseProber();

  virtual bool probe(const ChessBoard& board, score_t* score) = 0;
};

} // namespace olaf

#endif // TABLEBASEPROBER_H

