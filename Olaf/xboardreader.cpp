#include "xboardreader.h"
#include <sstream>

using namespace std;

XBoardReader::XBoardReader():
  m_engine (m_writer)
{}

void XBoardReader::run()
{
  m_engine.start();
  while (true) {
    string message;
    getline(cin, &message);
    istringstream iss (message);
    vector<string> tokens;
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string>>(tokens));
    if (tokens.empty()) {
      continue;
    }
    string command = tokens[0];
    switch (command) {
    case "protover":
      int version;
      cin >> version;
      if (version >= 2) {
        write_features();
      }
      break;
    case "accepted":
      break;
    case "rejected":
      break;
    case "quit":
      engine.shutdown();
      return;
    case "new":
      engine.reset();
      break;
    case "random":
      break;
    case "force":
      engine.request_stop();
      break;
    case "go":
      engine.resume(true);
      break;
    case "playother":
      engine.resume(false);
      break;
    case "?":
      engine.move_now();
      break;
    case "ping":
      m_writer.pong(tokens[1]);
      break;
    case "result":
      engine.request_stop();
      break;
    case "easy":
      engine.pondering(false);
      break;
    case "hard":
      engine.pondering(true);
      break;
    default:
      if (is_move(message)) {
        handle_move(message);
      } else {
        m_writer.unknown_command(message);
      }
    }
  }
}

static const string columns = "abcdefgh";
static const string rows = "012345678";
static const string conversions = "rbnq";

bool XBoardReader::is_move(const std::string& command) const
{
  if (
      command.length() < 4 ||
      columns.find(command[0]) == string::npos ||
      rows.find(command[1]) == string::npos ||
      columns.find(command[2]) == string::npos ||
      rows.find(command[3]) == string::npos
      ) {
    return false;
  }
  return command.length() == 4 || (command.length() == 5 && conversions.find(command[4]) != string::npos);
}

void XBoardReader::handle_move(const std::string& move) const
{
  if (!engine.move(move)) {
    m_writer.illegal_move(move);
  }
}

void XBoardReader::write_features() const
{
  m_writer.feature("ping", true);
  m_writer.feature("setboard", true);
  m_writer.feature("usermove", true);
  m_writer.feature("myname", "Olaf");
  m_writer.feature("variants", "normal");
  m_writer.feature("colors", false);
  m_writer.feature("ics", true);
  m_writer.feature("name", true);
  m_writer.feature("nps", false);
  m_writer.feature("pause", true);
  m_writer.feature("done", true);
}
