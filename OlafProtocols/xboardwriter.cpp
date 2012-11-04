#include "xboardwriter.h"
#include <iostream>

using namespace std;

void XBoardWriter::feature(const string& name, bool value) const
{
  cout << "feature " << name << " " << (value ? 1 : 0) << endl;
}

void XBoardWriter::feature(const string& name, int value) const
{
  cout << "feature " << name << " " << value << endl;
}

void XBoardWriter::feature(const string& name, const string& value) const
{
  cout << "feature " << name << " \"" << value << "\"" << endl;
}

void XBoardWriter::unknown_command(const string &command) const
{
  error("unknown command", command);
}

static const string rows = "12345678";

static const string columns = "abcdefgh";

void XBoardWriter::move(const Move &mov) const
{
  cout << "move "
       << columns[mov.source().column()]
       << rows[mov.source().row()]
       << columns[mov.destination().column()]
       << rows[mov.destination().row()];
  if (mov.is_conversion()) {
    if (mov.created_piece() == PieceSet::instance().bishop()->piece_index()) {
      cout << "b";
    } else if (mov.created_piece() == PieceSet::instance().knight()->piece_index()) {
      cout << "n";
    } else if (mov.created_piece() == PieceSet::instance().queen()->piece_index()) {
      cout << "q";
    } else if (mov.created_piece() == PieceSet::instance().rook()->piece_index()) {
      cout << "r";
    }
  }
  cout << endl;
}

void XBoardWriter::result(Result result, const string& comment) const
{
  switch (result) {
  case Win: cout << "1-0";
  case Lose: cout << "0-1";
  case Draw: cout << "1/2-1/2";
  }
  cout << " {" << comment << "}" << endl;
}

void XBoardWriter::resign() const
{
  cout << "resign" << endl;
}


void XBoardWriter::offer_draw() const
{
  cout << "offer draw" << endl;
}

void XBoardWriter::tell_opponent(const std::string &message) const
{
  cout << "tellopponent " << message << endl;
}

void XBoardWriter::tell_others(const std::string &message) const
{
  cout << "tellothers " << message << endl;
}

void XBoardWriter::tell_all(const std::string &message) const
{
  cout << "tellall " << message << endl;
}

void XBoardWriter::tell_user(const std::string &message) const
{
  cout << "telluser " << message << endl;
}

void XBoardWriter::tell_user_error(const std::string &message) const
{
  cout << "tellusererror " << message << endl;
}

void XBoardWriter::askuser(const std::string &rep_tag, const std::string &question) const
{
  cout << "askuser " << rep_tag << " " << question << endl;
}

void XBoardWriter::tell_ics(const std::string &message) const
{
  cout << "tellics " << message << endl;
}

void XBoardWriter::tell_ics_noalias(const std::string &message) const
{
  cout << "tellicsnoalias " << message << endl;
}

void XBoardWriter::comment(const std::string &message) const
{
  cout << "# " << message << endl;
}

void XBoardWriter::pong(const std::string& number) const
{
  cout << number << endl;
}

void XBoardWriter::error(const std::string& type, const std::string& message) const
{
  cout << "Error (" << type << "): " << message << endl;
}

void XBoardWriter::illegal_move(const std::string& move) const
{
  cout << "Illegal move: " << move << endl;
}

void XBoardWriter::illegal_move(const std::string& reason, const std::string& move) const
{
  cout << "Illegal move(" << reason << "): " << move << endl;
}
