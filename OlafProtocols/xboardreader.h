#ifndef XBOARDREADER_H
#define XBOARDREADER_H

#include "engineproducer.h"
#include "protocolreader.h"
#include "xboardwriter.h"
#include <string>
#include <memory>

class XBoardReader : public ProtocolReader
{
public:
  XBoardReader(const std::shared_ptr<XBoardWriter> &writer, const std::shared_ptr<EngineProducer> &engine);

  void run();

  bool is_move(const std::string&) const;

  void handle_move(const std::string&) const;

  void write_features() const;

private:
  std::shared_ptr<XBoardWriter> m_writer;

  std::shared_ptr<EngineProducer> m_engine;

};

#endif // XBOARDREADER_H
