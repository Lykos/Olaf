#include "xboardreader.h"
#include "OlafRules/piece.h"
#include "OlafRules/position.h"
#include "OlafRules/pieceset.h"
#include <sstream>
#include <iostream>
#include <iterator>

using namespace std;

XBoardReader::XBoardReader(const shared_ptr<XBoardWriter> &writer, const shared_ptr<EngineProducer> &engine):
  m_writer (writer),
  m_engine (engine)
{}

void XBoardReader::run()
{
  while (true) {
    string message;
    getline(cin, message);
    istringstream iss (message);
    vector<string> tokens;
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string>>(tokens));
    if (tokens.empty()) {
      continue;
    }
    string command = tokens[0];
    if (command == "protover") {
      int version;
      cin >> version;
      if (version >= 2) {
        write_features();
      }
      break;
    } else if (command == "accepted") {
      break;
    } else if (command == "rejected") {
      break;
    } else if (command == "quit") {
      m_engine->request_quit();
      return;
    } else if (command == "new") {
      m_engine->request_force(false);
      m_engine->request_reset();
      m_engine->request_deferred_pondering();
      m_engine->request_myturn(false);
      break;
    } else if (command == "random") {
      break;
    } else if (command == "force") {
      m_engine->request_force(true);
      break;
    } else if (command == "go") {
      m_engine->request_myturn(true);
      m_engine->request_force(false);
      break;
    } else if (command == "playother") {
      m_engine->request_myturn(false);
      m_engine->request_force(false);
      break;
    } else if (command == "?") {
      // TODO
      break;
    } else if (command == "ping") {
      m_engine->ping(tokens[1]);
      break;
    } else if (command == "result") {
      m_engine->request_force(true);
      break;
    } else if (command == "easy") {
      m_engine->request_pondering(false);
      break;
    } else if (command == "hard") {
      m_engine->request_pondering(true);
      break;
    } else {
      if (is_move(message)) {
        handle_move(message);
      } else {
        m_writer->unknown_command(message);
      }
    }
  }
}

static const string columns = "abcdefgh";
static const string rows = "012345678";
static const string conversions = "rbnq";

bool XBoardReader::is_move(const string& command) const
{
  if (
      command.size() < 4 ||
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
  Position source (rows.find(move[1]), columns.find(move[0]));
  Position destination (rows.find(move[3]), columns.find(move[2]));
  if (move.size() == 4) {
    if (!m_engine->request_move(source, destination)) {
      m_writer->illegal_move(move);
    }
  } else {
    Piece::piece_index_t conversion = -1;
    const PieceSet &set = PieceSet::instance();
    switch (move[4]) {
    case 'r':
      conversion = set.rook()->piece_index();
      break;
    case 'b':
      conversion = set.bishop()->piece_index();
      break;
    case 'q':
      conversion = set.queen()->piece_index();
      break;
    case 'n':
      conversion = set.knight()->piece_index();
      break;
    }
    if (!m_engine->request_move(source, destination, conversion)) {
      m_writer->illegal_move(move);
    }
  }
}

void XBoardReader::write_features() const
{
  m_writer->feature("ping", true);
  m_writer->feature("setboard", true);
  m_writer->feature("usermove", true);
  m_writer->feature("myname", "Olaf");
  m_writer->feature("variants", "normal");
  m_writer->feature("colors", false);
  m_writer->feature("ics", true);
  m_writer->feature("name", true);
  m_writer->feature("nps", false);
  m_writer->feature("pause", true);
  m_writer->feature("done", true);
}
