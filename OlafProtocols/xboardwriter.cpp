#include "xboardwriter.h"
#include <iostream>

using namespace std;

void XBoardWriter::newline()
{
  unique_lock<mutex> lock(m_mutex);
  cout << endl;
}

void XBoardWriter::feature(const string& name, bool value)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "feature " << name << "=" << (value ? 1 : 0) << endl;
}

void XBoardWriter::feature(const string& name, int value)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "feature " << name << "=" << value << endl;
}

void XBoardWriter::feature(const string& name, const string& value)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "feature " << name << " \"" << value << "\"" << endl;
}

void XBoardWriter::unknown_command(const string &command)
{
  unique_lock<mutex> lock(m_mutex);
  error("unknown command", command);
}

void XBoardWriter::move(const Move& mov)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "move "
       << mov.source()
       << mov.destination();
  if (mov.is_conversion()) {
    if (mov.created_piece() == PieceSet::instance().bishop().piece_index()) {
      cout << "b";
    } else if (mov.created_piece() == PieceSet::instance().knight().piece_index()) {
      cout << "n";
    } else if (mov.created_piece() == PieceSet::instance().queen().piece_index()) {
      cout << "q";
    } else if (mov.created_piece() == PieceSet::instance().rook().piece_index()) {
      cout << "r";
    }
  }
  cout << endl;
}

void XBoardWriter::result(Result result, const string& comment)
{
  unique_lock<mutex> lock(m_mutex);
  switch (result) {
  case Win: cout << "1-0";
  case Lose: cout << "0-1";
  case Draw: cout << "1/2-1/2";
  }
  cout << " {" << comment << "}" << endl;
}

void XBoardWriter::resign()
{
  unique_lock<mutex> lock(m_mutex);
  cout << "resign" << endl;
}


void XBoardWriter::offer_draw()
{
  unique_lock<mutex> lock(m_mutex);
  cout << "offer draw" << endl;
}

void XBoardWriter::tell_opponent(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "tellopponent " << message << endl;
}

void XBoardWriter::tell_others(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "tellothers " << message << endl;
}

void XBoardWriter::tell_all(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "tellall " << message << endl;
}

void XBoardWriter::tell_user(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "telluser " << message << endl;
}

void XBoardWriter::tell_user_error(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "tellusererror " << message << endl;
}

void XBoardWriter::askuser(const string& rep_tag, const string& question)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "askuser " << rep_tag << " " << question << endl;
}

void XBoardWriter::tell_ics(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "tellics " << message << endl;
}

void XBoardWriter::tell_ics_noalias(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "tellicsnoalias " << message << endl;
}

void XBoardWriter::comment(const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "# " << message << endl;
}

void XBoardWriter::pong(int number)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "pong " << number << endl;
}

void XBoardWriter::error(const string& type, const string& message)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "Error (" << type << "): " << message << endl;
}

void XBoardWriter::illegal_move(const string& move)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "Illegal move: " << move << endl;
}

void XBoardWriter::illegal_move(const string& reason, const string& move)
{
  unique_lock<mutex> lock(m_mutex);
  cout << "Illegal move(" << reason << "): " << move << endl;
}

void XBoardWriter::thinking_output(int ply, int score, int centiseconds, int nodes, const string& moves)
{
  unique_lock<mutex> lock(m_mutex);
  cout << ply << "\t" << score << "\t" << centiseconds << "\t" << nodes << "\t" << moves << endl;
}
