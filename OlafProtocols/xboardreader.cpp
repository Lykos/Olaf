#include "xboardreader.h"
#include "OlafRules/piece.h"
#include "OlafRules/position.h"
#include "OlafRules/pieceset.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <chrono>

using namespace std;
using namespace chrono;

XBoardReader::XBoardReader(XBoardWriter* const writer, unique_ptr<EngineEventHelper> engine_helper):
  m_writer(writer),
  m_engine_helper(move(engine_helper))
{}

void XBoardReader::run()
{
  m_writer->newline();
  while (!cin.eof()) {
    cout << "# Reading command" << endl;
    string message;
    getline(cin, message);
    istringstream iss (message);
    vector<string> tokens;
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string>>(tokens));
    if (tokens.empty()) {
      continue;
    }
    string command = tokens[0];
    cout << "# Understood command " << command << endl;
    if (command == "protover") {
      int version;
      istringstream iss (tokens[1]);
      iss >> version;
      if (version >= 2) {
        write_features();
      }
    } else if (command == "accepted") {
    } else if (command == "rejected") {
    } else if (command == "quit") {
      break;
    } else if (command == "new") {
      m_engine_helper->request_force(true);
      m_engine_helper->request_reset();
      m_engine_helper->request_deferred_pondering();
      m_engine_helper->request_myturn(false);
      m_engine_helper->request_force(false);
    } else if (command == "random") {
    } else if (command == "force") {
      m_engine_helper->request_force(true);
    } else if (command == "go") {
      m_engine_helper->request_myturn(true);
      m_engine_helper->request_force(false);
    } else if (command == "playother") {
      m_engine_helper->request_myturn(false);
      m_engine_helper->request_force(false);
    } else if (command == "?") {
      m_engine_helper->move_now();
    } else if (command == "ping") {
      int number;
      istringstream iss (tokens[1]);
      iss >> number;
      m_engine_helper->ping(number);
    } else if (command == "result") {
      m_engine_helper->request_force(true);
    } else if (command == "easy") {
      m_engine_helper->request_pondering(false);
    } else if (command == "hard") {
      m_engine_helper->request_pondering(true);
    } else if (command == "name") {
    } else if (command == "ics") {
    } else if (command == "time") {
      istringstream iss (tokens[1]);
      int centiseconds;
      iss >> centiseconds;
      m_engine_helper->request_set_time(milliseconds(centiseconds * 10));
    } else if (command == "otim") {
    } else if (command == "computer") {
    } else if (command == "level") {
      // TODO
    } else if (command == "usermove") {
      if (is_move(tokens[1])) {
        handle_move(tokens[1]);
      } else {
        m_writer->illegal_move(message);
      }
    } else {
      if (is_move(message)) {
        handle_move(message);
      } else {
        m_writer->unknown_command(message);
      }
    }
  }
  m_engine_helper->request_quit();
}

static const string conversions = "rbnq";

bool XBoardReader::is_move(const string& command) const
{
  if (
      command.size() < 4 ||
      Position::columns.find(command[0]) == string::npos ||
      Position::rows.find(command[1]) == string::npos ||
      Position::columns.find(command[2]) == string::npos ||
      Position::rows.find(command[3]) == string::npos
      ) {
    return false;
  }
  return command.length() == 4 || (command.length() == 5 && conversions.find(command[4]) != string::npos);
}

void XBoardReader::handle_move(const std::string& move) const
{
  Position source;
  Position destination;
  istringstream iss (move);
  iss >> source >> destination;
  if (move.size() == 4) {
    if (!m_engine_helper->request_move(source, destination)) {
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
    if (!m_engine_helper->request_move(source, destination, conversion)) {
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
  m_writer->feature("debug", true);
  m_writer->feature("sigint", false);
  m_writer->feature("done", true);
}
