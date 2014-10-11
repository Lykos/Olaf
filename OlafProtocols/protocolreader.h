#ifndef PROTOCOL_H
#define PROTOCOL_H

/**
 * @brief The ProtocolReader class is an abstract class which is
 *        responsible for reading messages from the chess program interface.
 */
class ProtocolReader
{
public:
  virtual void run() = 0;

  ~ProtocolReader() {}

};

#endif // PROTOCOL_H
