#ifndef XBOARDREADER_H
#define XBOARDREADER_H

#include <string>
#include <memory>
#include <istream>

#include "engineeventhelper.h"
#include "protocolreader.h"
#include "xboardwriter.h"

class XBoardReader : public ProtocolReader
{
public:
  /**
   * @brief XBoardReader takes ownership of engine_helper but not of writer or in.
   */
  XBoardReader(XBoardWriter* writer,
               std::unique_ptr<EngineEventHelper> engine_helper,
               std::istream* in);

  void run() override;

  bool is_move(const std::string& command) const;

  void handle_move(const std::string& move);

  void write_features() const;
private:
  XBoardWriter* const m_writer;

  std::unique_ptr<EngineEventHelper> m_engine_helper;

  std::istream* const m_in;
};

#endif // XBOARDREADER_H
