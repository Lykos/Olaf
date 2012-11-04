#ifndef PROTOCOLWRITER_H
#define PROTOCOLWRITER_H

#include "OlafRules/move.h"
#include <string>

class ProtocolWriter
{
public:
  virtual void move(const Move &move) const = 0;

  virtual void pong(const std::string&) const = 0;

  virtual ~ProtocolWriter() {}
};

#endif // PROTOCOLWRITER_H
