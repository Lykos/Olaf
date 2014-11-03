#ifndef ENGINESTATE_H
#define ENGINESTATE_H

#include <chrono>
#include <memory>

#include "olaf/search/searchcontext.h"
#include "olaf/search/forcedstopper.h"
#include "olaf/transposition_table/transpositiontable.h"
#include "olaf/tablebases/egbbprober.h"

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
                       std::unique_ptr<EgbbProber> eggb_prober,
                       BoardState* board_state);

  inline bool pondering() const { return m_pondering && !m_deferred_pondering; }

  inline void pondering(const bool value) { m_pondering = value; }

  inline bool my_turn() const { return m_my_turn; }

  inline void my_turn(const bool value) { m_my_turn = value; }

  inline void flip_turn() { m_deferred_pondering = false; m_my_turn = !m_my_turn; }

  inline bool force() const { return m_force; }

  inline void force(const bool value) { m_force = value; }

  inline void deferred_pondering() { m_deferred_pondering = true; m_pondering = true; }

  inline std::chrono::milliseconds my_time() const { return m_my_time; }

  inline void my_time(const std::chrono::milliseconds& time) { m_my_time = time; }

  inline std::chrono::milliseconds opponent_time() const { return m_opponent_time; }

  inline void opponent_time(const std::chrono::milliseconds& time) { m_opponent_time = time; }

  inline void level(const int moves_to_play,
                    const std::chrono::milliseconds& total_time,
                    const std::chrono::milliseconds& increment) {
    m_my_time = total_time;
    m_opponent_time = total_time;
    m_increment = increment;
    m_moves = moves_to_play;
  }

  inline bool analyze() const { return m_analyze; }

  inline void analyze(const bool value) { m_analyze = value; }

  inline bool use_nps() const { return m_use_nps; }

  inline void use_nps(const bool value) { m_use_nps = value; }

  inline bool nps() const { return m_nps; }

  inline void nps(const bool value) { m_nps = value; }

  inline bool use_depth() const { return m_use_depth; }

  inline void use_depth(const int value) { m_use_depth = value; }

  inline bool depth() const { return m_depth; }

  inline void depth(const int value) { m_depth = value; }

  inline const BoardState& board_state() const { return *m_board_state; }

  inline BoardState& board_state() { return *m_board_state; }

  void reset_stoppers();

  SearchContext create_search_context();

  inline void stop() { m_forced_stopper.request_stop(); }

  inline void weak_stop() { m_weak_stopper.request_stop(); }

  void set_egt_path(const std::string& path);

private:
  std::unique_ptr<TranspositionTable> m_transposition_table;

  std::unique_ptr<EgbbProber> m_egbb_prober;

  ForcedStopper m_forced_stopper;

  ForcedStopper m_weak_stopper;

  BoardState* const m_board_state;

  bool m_my_turn = false;

  bool m_pondering = true;

  bool m_force = true;

  bool m_deferred_pondering = true;

  bool m_use_nps = false;

  bool m_use_depth = false;

  bool m_analyze = false;

  int m_depth;

  int m_nps;

  int m_moves = 0;

  std::chrono::milliseconds m_my_time;

  std::chrono::milliseconds m_opponent_time;

  std::chrono::milliseconds m_increment;
};

} // namespace olaf

#endif // ENGINESTATE_H
