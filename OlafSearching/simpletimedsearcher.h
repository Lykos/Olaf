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
  explicit SimpleTimedSearcher(std::unique_ptr<IterativeSearcher> searcher,
                               const std::chrono::milliseconds& search_millis);

  SearchResult search_timed(ChessBoard* board,
                            const Stopper& forced_stopper,
                            const Stopper& weak_stopper);

  SearchResult search_untimed(ChessBoard* board,
                              const Stopper& forced_stopper);

private:
  std::unique_ptr<IterativeSearcher> m_searcher;
  const std::chrono::milliseconds m_search_millis;
};

#endif // SIMPLETIMEDSEARCHER_H
