#ifndef PROTOCOLWRITER_H
#define PROTOCOLWRITER_H

#include "olaf/rules/move.h"

namespace olaf
{

/**
 * @brief The ProtocolWriter class is an abstract class which is
 *        responsible for writing answers to the chess program interface.
 */
class ProtocolWriter
{
public:
  virtual void move(const Move& move) = 0;

  virtual void pong(int number) = 0;

  virtual void comment(const std::string& message) = 0;

  virtual void thinking_output(int ply, int score, int centiseconds, int nodes, const std::string& moves) = 0;

  virtual ~ProtocolWriter();
};

} // namespace olaf

#endif // PROTOCOLWRITER_H
