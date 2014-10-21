#include "xboardwriter.h"

#include <iostream>

#include "olaf/rules/pieceset.h"
#include "olaf/rules/move.h"

using namespace std;

namespace olaf
{

XBoardWriter::XBoardWriter(ostream* const out):
  m_out(out)
{}

XBoardWriter::~XBoardWriter()
{}

void XBoardWriter::newline()
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << endl;
}

void XBoardWriter::feature(const string& name, bool value)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "feature " << name << "=" << (value ? 1 : 0) << endl;
}

void XBoardWriter::feature(const string& name, int value)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "feature " << name << "=" << value << endl;
}

void XBoardWriter::feature(const string& name, const string& value)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "feature " << name << " \"" << value << "\"" << endl;
}

void XBoardWriter::unknown_command(const string &command)
{
  unique_lock<mutex> lock(m_mutex);
  error(ErrorType::UNKNOWN_COMMAND, command);
}

void XBoardWriter::move(const Move& mov)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "move "
         << mov.source()
         << mov.destination();
  if (mov.is_promotion()) {
    *m_out << PieceSet::instance().piece(mov.created_piece()).symbol(Color::Black);
  }
  *m_out << endl;
}

void XBoardWriter::result(Result result, const string& comment)
{
  unique_lock<mutex> lock(m_mutex);
  switch (result) {
  case Win: *m_out << "1-0";
  case Lose: *m_out << "0-1";
  case Draw: *m_out << "1/2-1/2";
  }
  *m_out << " {" << comment << "}" << endl;
}

void XBoardWriter::resign()
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "resign" << endl;
}


void XBoardWriter::offer_draw()
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "offer draw" << endl;
}

void XBoardWriter::tell_opponent(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "tellopponent " << message << endl;
}

void XBoardWriter::tell_others(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "tellothers " << message << endl;
}

void XBoardWriter::tell_all(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "tellall " << message << endl;
}

void XBoardWriter::tell_user(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "telluser " << message << endl;
}

void XBoardWriter::tell_user_error(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "tellusererror " << message << endl;
}

void XBoardWriter::askuser(const string& rep_tag, const string& question)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "askuser " << rep_tag << " " << question << endl;
}

void XBoardWriter::tell_ics(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "tellics " << message << endl;
}

void XBoardWriter::tell_ics_noalias(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "tellicsnoalias " << message << endl;
}

void XBoardWriter::comment(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "# " << message << endl;
}

void XBoardWriter::pong(int number)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "pong " << number << endl;
}

void XBoardWriter::error(const ErrorType type, const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "Error (" << error_name(type) << "): " << message << endl;
}

void XBoardWriter::illegal_move(const string& move)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "Illegal move: " << move << endl;
}

void XBoardWriter::illegal_move(const string& reason, const string& move)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "Illegal move(" << reason << "): " << move << endl;
}

void XBoardWriter::thinking_output(const int ply,
                                   const int score,
                                   const int centiseconds,
                                   const int nodes,
                                   const string& moves)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << ply << "\t" << score << "\t" << centiseconds << "\t" << nodes << "\t" << moves << endl;
}

std::string XBoardWriter::error_name(const ErrorType type) const
{
  switch (type) {
    case ErrorType::UNKNOWN_COMMAND:
      return "unknown command";
    case ErrorType::NOT_ENOUGH_ARGUMENTS:
      return "not enough arguments";
    case ErrorType::INVALID_FEN:
      return "invalid fen";
  }
  return "";

} // namespace olaf
}
