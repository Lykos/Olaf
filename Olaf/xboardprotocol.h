#ifndef XBOARDPROTOCOL_H
#define XBOARDPROTOCOL_H

#include "engine.h"
#include "protocol.h"
#include <string>

class XBoardProtocol : public Protocol
{
public:
  XBoardProtocol();

  void run();

  static const std::string& name();

  void write_features() const;

  void unknown_command(const std::string&) const;

  bool is_move(const std::string&) const;

  void handle_move(const std::string&) const;

private:
  Engine engine;

};

#endif // XBOARDPROTOCOL_H
