#ifndef XBOARDPROTOCOL_H
#define XBOARDPROTOCOL_H

#include "engine.h"
#include "protocolreader.h"
#include "xboardwriter.h"
#include <string>

class XBoardReader : public ProtocolReader
{
public:
  XBoardReader();

  void run();

  bool is_move(const std::string&) const;

  void handle_move(const std::string&) const;

  void write_features() const;

private:
  XBoardWriter m_writer;

  Engine m_engine;

};

#endif // XBOARDPROTOCOL_H
