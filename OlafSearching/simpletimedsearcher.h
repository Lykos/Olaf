#ifndef SIMPLETIMEDSEARCHER_H
#define SIMPLETIMEDSEARCHER_H

#include "timedsearcher.h"
#include "OlafRules/chessboard.h"
#include "stopper.h"
#include "searchresult.h"
#include "iterativesearcher.h"
#include "timestopper.h"
#include <memory>
#include <chrono>

class SimpleTimedSearcher : public TimedSearcher
{
public:
  explicit SimpleTimedSearcher(const std::shared_ptr<IterativeSearcher> &searcher);

  SearchResult search(ChessBoard &board, const std::shared_ptr<Stopper> &forced_stopper, const std::shared_ptr<Stopper>& weak_stopper);

private:
  std::shared_ptr<IterativeSearcher> m_searcher;

};

#endif // SIMPLETIMEDSEARCHER_H
