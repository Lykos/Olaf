#ifndef PROTOCOLWRITER_H
#define PROTOCOLWRITER_H

#include "OlafRules/move.h"

class ProtocolWriter
{
public:
  virtual void move(const Move &move) const = 0;

  virtual void pong(int number) const = 0;

  virtual void comment(const std::string &message) const = 0;

  virtual ~ProtocolWriter() = 0;
};

#endif // PROTOCOLWRITER_H
