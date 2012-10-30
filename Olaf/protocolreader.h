#ifndef PROTOCOL_H
#define PROTOCOL_H

class ProtocolReader
{
public:
  virtual void run() = 0;

  ~ProtocolReader() {}

};

#endif // PROTOCOL_H
