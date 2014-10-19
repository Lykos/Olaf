#ifndef ENGINESTATE_H
#define ENGINESTATE_H

#include <chrono>

#include "olaf/search/searchcontext.h"

namespace olaf
{

class BoardState;

/**
 * @brief The EngineState class represents the state of the engine
 *        i.e. the board, the time and the options.
 */
class EngineState
{
public:
  explicit EngineState(BoardState* board_state);

  bool pondering() const;

  void pondering(bool value);

  bool my_turn() const;

  void my_turn(bool value);

  void flip_turn();

  bool force() const;

  void force(bool value);

  void deferred_pondering();

  std::chrono::milliseconds time() const;

  void time(const std::chrono::milliseconds& time);

  const BoardState& board_state() const;

  BoardState& board_state();

  SearchContext create_search_context(const Stopper* forced_stopper,
                                      const Stopper* weak_stopper) const;

private:
  BoardState* const m_board_state;

  bool m_my_turn = false;

  bool m_pondering = true;

  bool m_force = true;

  bool m_deferred_pondering = true;

  std::chrono::milliseconds m_time;

};

} // namespace olaf

#endif // ENGINESTATE_H
