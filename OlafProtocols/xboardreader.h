#ifndef XBOARDREADER_H
#define XBOARDREADER_H

#include "engineeventhelper.h"
#include "protocolreader.h"
#include "xboardwriter.h"
#include <string>
#include <memory>

class XBoardReader : public ProtocolReader
{
public:
  /**
   * @brief XBoardReader takes ownership of engine_helper but not of writer.
   */
  XBoardReader(XBoardWriter* writer, std::unique_ptr<EngineEventHelper> engine_helper);

  void run() override;

  bool is_move(const std::string& command) const;

  void handle_move(const std::string& move);

  void write_features() const;
private:
  XBoardWriter* const m_writer;

  std::unique_ptr<EngineEventHelper> m_engine_helper;
};

#endif // XBOARDREADER_H
