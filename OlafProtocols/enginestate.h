#ifndef ENGINESTATE_H
#define ENGINESTATE_H

class EngineState
{
public:
  bool pondering() const;

  void pondering(bool value);

  bool my_turn() const;

  void my_turn(bool value);

  bool force() const;

  void force(bool value);

  void deferred_pondering();

private:
  bool m_my_turn;

  bool m_pondering;

  bool m_force;

  bool m_deferred_pondering = false;

};

#endif // ENGINESTATE_H
