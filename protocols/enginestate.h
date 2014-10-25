#ifndef ENGINESTATE_H
#define ENGINESTATE_H

#include <chrono>
#include <memory>

#include "olaf/search/searchcontext.h"
#include "olaf/transposition_table/transpositiontable.h"

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
  explicit EngineState(std::unique_ptr<TranspositionTable> transposition_table,
                       BoardState* board_state);

  bool pondering() const { return m_pondering && !m_deferred_pondering; }

  void pondering(const bool value) { m_pondering = value; }

  bool my_turn() const { return m_my_turn; }

  void my_turn(const bool value) { m_my_turn = value; }

  void flip_turn() { m_deferred_pondering = false; m_my_turn = !m_my_turn; }

  bool force() const { return m_force; }

  void force(const bool value) { m_force = value; }

  void deferred_pondering() { m_deferred_pondering = true; m_pondering = true; }

  std::chrono::milliseconds my_time() const { return m_my_time; }

  void my_time(const std::chrono::milliseconds& time) { m_my_time = time; }

  std::chrono::milliseconds opponent_time() const { return m_opponent_time; }

  void opponent_time(const std::chrono::milliseconds& time) { m_opponent_time = time; }

  bool use_nps() const { return m_use_nps; }

  void use_nps(const bool value) { m_use_nps = value; }

  bool nps() const { return m_nps; }

  void nps(const bool value) { m_nps = value; }

  bool use_depth() const { return m_use_depth; }

  void use_depth(const int value) { m_use_depth = value; }

  bool depth() const { return m_depth; }

  void depth(const int value) { m_depth = value; }

  const BoardState& board_state() const { return *m_board_state; }

  BoardState& board_state() { return *m_board_state; }

  SearchContext create_search_context(const Stopper* forced_stopper,
                                      const Stopper* weak_stopper) const;

private:
  std::unique_ptr<TranspositionTable> m_transposition_table;

  BoardState* const m_board_state;

  bool m_my_turn = false;

  bool m_pondering = true;

  bool m_force = true;

  bool m_deferred_pondering = true;

  bool m_use_nps = false;

  bool m_use_depth = false;

  int m_depth;

  int m_nps;

  std::chrono::milliseconds m_my_time;

  std::chrono::milliseconds m_opponent_time;
};

} // namespace olaf

#endif // ENGINESTATE_H
