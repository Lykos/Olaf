#ifndef TIMEDSEARCHER_H
#define TIMEDSEARCHER_H

#include "OlafRules/chessboard.h"
#include "stopper.h"
#include "searchresult.h"
#include <memory>
#include <chrono>

class TimedSearcher
{
public:
  /**
   * @brief search_timed searches and keeps an eye on the time
   * @param board
   * @param forced_stopper A stopper that also applies in the first round, before any move has been found.
   * @param weak_stopper A stopper that only applies after a move has been found.
   * @return
   */
  virtual SearchResult search_timed(ChessBoard* board,
                                    const Stopper& forced_stopper,
                                    const Stopper& weak_stopper) = 0;

  /**
   * @brief search_untimed just searches until interrupted
   * @param board
   * @param forced_stopper A stopper that also applies in the first round, before any move has been found.
   * @param weak_stopper A stopper that only applies after a move has been found.
   * @return
   */
  virtual SearchResult search_untimed(ChessBoard* board,
                                      const Stopper& forced_stopper) = 0;

  virtual ~TimedSearcher() = 0;

  void time(const std::chrono::milliseconds &time);

  std::chrono::milliseconds time() const;

private:
  std::chrono::milliseconds m_time;

  std::chrono::steady_clock::time_point m_start;
};

#endif // TIMEDSEARCHER_H
