#ifndef PROTOCOLWRITER_H
#define PROTOCOLWRITER_H

#include "OlafRules/move.h"

class ProtocolWriter
{
public:
  virtual void move(const Move &move) = 0;

  virtual void pong(int number) = 0;

  virtual void comment(const std::string &message) = 0;

  virtual void thinking_output(int ply, int score, int centiseconds, int nodes, const std::string &moves) = 0;

  virtual ~ProtocolWriter() = 0;
};

#endif // PROTOCOLWRITER_H
