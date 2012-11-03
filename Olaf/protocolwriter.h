#ifndef PROTOCOLWRITER_H
#define PROTOCOLWRITER_H

#include "move.h"

class ProtocolWriter
{
public:
  virtual void move(const Move& move) = 0;

  virtual ~ProtocolWriter() {}
};

#endif // PROTOCOLWRITER_H
