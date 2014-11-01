#include "xboardreader.h"

#include <cassert>
#include <sstream>
#include <istream>
#include <iostream>
#include <iterator>
#include <chrono>

#include "olaf/rules/piece.h"
#include "olaf/rules/position.h"
#include "olaf/rules/pieceset.h"

using namespace std;
using namespace chrono;

namespace olaf
{

XBoardReader::XBoardReader(XBoardWriter* const writer,
                           unique_ptr<EngineEventHelper> engine_helper,
                           istream* const in):
  m_writer(writer),
  m_engine_helper(move(engine_helper)),
  m_in(in)
{}

static const char c_colon = ':';

void XBoardReader::run()
{
  m_engine_helper->request_reset();
  m_engine_helper->request_myturn(false);
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
    } else if (command == "hint") {
    } else if (command == "bk") {
    } else if (command == "time") {
      if (!check_args(tokens, 1)) {
        continue;
      }
      istringstream iss(tokens.at(1));
      int centiseconds;
      iss >> centiseconds;
      m_engine_helper->request_set_time(milliseconds(centiseconds * 10));
    } else if (command == "sd") {
      if (!check_args(tokens, 1)) {
        continue;
      }
      istringstream iss(tokens.at(1));
      int depth;
      iss >> depth;
      m_engine_helper->request_set_depth(depth);
    } else if (command == "nps") {
      if (!check_args(tokens, 1)) {
        continue;
      }
      istringstream iss(tokens.at(1));
      int nps;
      iss >> nps;
      m_engine_helper->request_set_depth(nps);
    } else if (command == "otim") {
      if (!check_args(tokens, 1)) {
        continue;
      }
      istringstream iss(tokens.at(1));
      int centiseconds;
      iss >> centiseconds;
      m_engine_helper->request_set_opponent_time(milliseconds(centiseconds * 10));
    } else if (command == "computer") {
    } else if (command == "draw") {
    } else if (command == "analyze") {
      m_engine_helper->request_analyze(true);
    } else if (command == "exit") {
      m_engine_helper->request_analyze(false);
    } else if (command == "undo") {
      if (!m_engine_helper->request_undo()) {
        m_writer->error(XBoardWriter::ErrorType::NO_UNDOABLE_MOVES, "It is not possible to undo a move.");
      }
    } else if (command == "remove") {
      if (!m_engine_helper->request_undo(2)) {
        m_writer->error(XBoardWriter::ErrorType::NO_UNDOABLE_MOVES, "It is not possible to undo two moves.");
      }
    } else if (command == "result") {
      m_engine_helper->request_force(true);
    } else if (command == "level") {
      if (!check_args(tokens, 3)) {
        continue;
      }
      istringstream iss1(tokens.at(1));
      int moves;
      iss1 >> moves;
      istringstream iss2(tokens.at(2));
      int time_min;
      iss2 >> time_min;
      int time_s = 0;
      if (iss2.peek() == c_colon) {
        iss2.get();
        iss2 >> time_s;
      }
      istringstream iss3(tokens.at(3));
      int increment_s;
      iss3 >> increment_s;
      const milliseconds total_time = minutes(time_min) + seconds(time_s);
      const milliseconds increment = seconds(increment_s);
      m_engine_helper->set_level(moves, total_time, increment);
    } else if (command == "post") {
      m_engine_helper->post(true);
    } else if (command == "nopost") {
      m_engine_helper->post(false);
    } else if (command == "variant") {
      if (!check_args(tokens, 1)) {
        continue;
      }
      const string& variant = tokens.at(1);
      if (variant != "normal") {
        ostringstream oss;
        oss << "Unknown variant \"" << variant << "\"";
        m_writer->error(XBoardWriter::ErrorType::UNKNOWN_VARIANT, oss.str());
      }
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
      if (!m_engine_helper->request_set_fen(fen)) {
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
    if (!m_engine_helper->request_move(IncompleteMove(source, destination))) {
      m_writer->illegal_move(move);
    }
  } else if (move.size() == 5) {
    Piece::piece_index_t created_piece = Piece::c_no_piece;
    for (const Piece* const piece : PieceSet::instance().pieces()) {
      if (piece->symbol(Color::Black) == move[4]) {
        created_piece = piece->piece_index();
        break;
      }
    }
    if (created_piece == Piece::c_no_piece) {
      m_writer->illegal_move(move);
      return;
    }
    if (!m_engine_helper->request_move(IncompleteMove::promotion(source, destination, created_piece))) {
      m_writer->illegal_move(move);
    }
  } else {
    m_writer->illegal_move(move);
  }
}

void XBoardReader::write_features() const
{
  m_writer->feature_bool("ping", true);
  m_writer->feature_bool("setboard", true);
  m_writer->feature_bool("usermove", true);
  m_writer->feature_string("myname", "olaf");
  m_writer->feature_string("variants", "normal");
  m_writer->feature_bool("colors", false);
  m_writer->feature_bool("ics", true);
  m_writer->feature_bool("name", true);
  m_writer->feature_bool("nps", false);
  m_writer->feature_bool("analyze", true);
  m_writer->feature_bool("pause", true);
  m_writer->feature_bool("debug", true);
  m_writer->feature_bool("sigint", false);
  m_writer->feature_bool("done", true);
  m_writer->feature_bool("playother", true);
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

} // namespace olaf
}
