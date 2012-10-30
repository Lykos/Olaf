#ifndef UCIPROTOCOL_H
#define UCIPROTOCOL_H

#include "protocol.h"
#include <string>

class UCIProtocol : public Protocol
{
public:
  void run();

  static const std::string& name();

};

#endif // UCIPROTOCOL_H
