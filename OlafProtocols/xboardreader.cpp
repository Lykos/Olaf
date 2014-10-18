#include "xboardreader.h"

#include <cassert>
#include <sstream>
#include <istream>
#include <iostream>
#include <iterator>
#include <chrono>

#include "OlafSearching/piece.h"
#include "OlafSearching/position.h"
#include "OlafSearching/pieceset.h"

using namespace std;
using namespace chrono;

XBoardReader::XBoardReader(XBoardWriter* const writer,
                           unique_ptr<EngineEventHelper> engine_helper,
                           istream* const in):
  m_writer(writer),
  m_engine_helper(move(engine_helper)),
  m_in(in)
{}

void XBoardReader::run()
{
  while (!m_in->eof()) {
    string message;
    getline(*m_in, message);
    istringstream iss(message);
    vector<string> tokens;
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string>>(tokens));
    if (tokens.empty()) {
      continue;
    }
    string command = tokens.front();
    if (command == "protover") {
      if (!check_args(tokens, 1)) {
        continue;
      }
      int version;
      istringstream iss(tokens.at(1));
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
      if (!check_args(tokens, 1)) {
        continue;
      }
      int number;
      istringstream iss(tokens.at(1));
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
      if (!check_args(tokens, 1)) {
        continue;
      }
      istringstream iss(tokens.at(1));
      int centiseconds;
      iss >> centiseconds;
      m_engine_helper->request_set_time(milliseconds(centiseconds * 10));
    } else if (command == "otim") {
    } else if (command == "computer") {
    } else if (command == "level") {
      // TODO
    } else if (command == "post") {
      m_engine_helper->post(true);
    } else if (command == "nopost") {
      m_engine_helper->post(false);
    } else if (command == "setboard") {
      ostringstream oss;
      int size = tokens.size();
      // We have to put the fen back together.
      for (int i = 1; i < size; ++i) {
        oss << tokens.at(i);
        if (i < size - 1) {
          oss << " ";
        }
      }
      const string fen = oss.str();
      if (!m_engine_helper->set_fen(fen)) {
        m_writer->error(XBoardWriter::ErrorType::INVALID_FEN, fen);
      }
    } else if (command == "usermove") {
      if (!check_args(tokens, 1)) {
        continue;
      }
      const string& move = tokens.at(1);
      if (is_move(move)) {
        handle_move(move);
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
  if (command.size() < 4
      || Position::columns.find(command[0]) == string::npos
      || Position::rows.find(command[1]) == string::npos
      || Position::columns.find(command[2]) == string::npos
      || Position::rows.find(command[3]) == string::npos) {
    return false;
  }
  if (command.length() == 4) {
    return true;
  } else if (command.length() == 5) {
    return conversions.find(command[4]) != string::npos;
  } else {
    return false;
  }
}

void XBoardReader::handle_move(const std::string& move)
{
  assert(is_move(move));
  Position source;
  Position destination;
  istringstream iss(move);
  iss >> source >> destination;
  if (move.size() == 4) {
    if (!m_engine_helper->request_move(source, destination)) {
      m_writer->illegal_move(move);
    }
  } else if (move.size() == 5) {
    Piece::piece_index_t conversion = -1;
    const PieceSet &set = PieceSet::instance();
    switch (move[4]) {
    case 'r':
      conversion = set.rook().piece_index();
      break;
    case 'b':
      conversion = set.bishop().piece_index();
      break;
    case 'q':
      conversion = set.queen().piece_index();
      break;
    case 'n':
      conversion = set.knight().piece_index();
      break;
    default:
      m_writer->illegal_move(move);
      return;
    }
    if (!m_engine_helper->request_move(source, destination, conversion)) {
      m_writer->illegal_move(move);
    }
  } else {
    m_writer->illegal_move(move);
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

bool XBoardReader::check_args(const vector<string>& tokens,
                              const int args) const
{
  // Note that the first token is the command.
  const int actual_args = tokens.size() - 1;
  const bool result = actual_args >= args;
  if (!result) {
    ostringstream oss;
    oss << "Wrong number of arguments for " << tokens.at(0)
        << ": " << args << " needed, " << actual_args
        << " provided.";
    m_writer->error(XBoardWriter::ErrorType::NOT_ENOUGH_ARGUMENTS, oss.str());
  }
  return result;
}
