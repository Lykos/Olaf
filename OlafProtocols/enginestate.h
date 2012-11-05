#ifndef ENGINESTATE_H
#define ENGINESTATE_H

#include <chrono>

/**
 * @brief The EngineState class represents the state of the engine except for the board, i.e. the time and the options.
 */
class EngineState
{
public:
  bool pondering() const;

  void pondering(bool value);

  bool my_turn() const;

  void my_turn(bool value);

  void flip_turn();

  bool force() const;

  void force(bool value);

  void deferred_pondering();

  std::chrono::milliseconds time() const;

  void time(const std::chrono::milliseconds &time);

private:
  bool m_my_turn = false;

  bool m_pondering = true;

  bool m_force = true;

  bool m_deferred_pondering = false;

  std::chrono::milliseconds m_time;

};

#endif // ENGINESTATE_H
