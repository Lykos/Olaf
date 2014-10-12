#include "xboardwriter.h"

#include <iostream>

#include "OlafRules/pieceset.h"

using namespace std;

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
  error("unknown command", command);
}

void XBoardWriter::move(const Move& mov)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "move "
       << mov.source()
       << mov.destination();
  if (mov.is_conversion()) {
    if (mov.created_piece() == PieceSet::instance().bishop().piece_index()) {
      *m_out << "b";
    } else if (mov.created_piece() == PieceSet::instance().knight().piece_index()) {
      *m_out << "n";
    } else if (mov.created_piece() == PieceSet::instance().queen().piece_index()) {
      *m_out << "q";
    } else if (mov.created_piece() == PieceSet::instance().rook().piece_index()) {
      *m_out << "r";
    }
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

void XBoardWriter::error(const string& type, const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << "Error (" << type << "): " << message << endl;
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

void XBoardWriter::thinking_output(int ply, int score, int centiseconds, int nodes, const string& moves)
{
  unique_lock<mutex> lock(m_mutex);
  *m_out << ply << "\t" << score << "\t" << centiseconds << "\t" << nodes << "\t" << moves << endl;
}
