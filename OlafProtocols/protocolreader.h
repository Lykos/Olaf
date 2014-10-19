#ifndef PROTOCOL_H
#define PROTOCOL_H

namespace olaf
{

/**
 * @brief The ProtocolReader class is an abstract class which is
 *        responsible for reading messages from the chess program interface.
 */
class ProtocolReader
{
public:
  virtual ~ProtocolReader();

  virtual void run() = 0;

};

} // namespace olaf

#endif // PROTOCOL_H
