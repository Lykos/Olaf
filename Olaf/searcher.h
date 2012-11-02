#ifndef SEARCHER_H
#define SEARCHER_H

#include "chessboard.h"
#include "searchresult.h"

class Searcher {
public:
  virtual SearchResult search(ChessBoard &board, int depth) = 0;

  void request_stop();

  virtual ~Searcher() {}

protected:
  bool should_stop() const;

  void stopped();

private:
  volatile bool m_should_stop = false;

};

#endif // SEARCHER_H
