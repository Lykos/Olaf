#include "xboardwriter.h"

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

void XBoardWriter::move(const Move &move) const
{
  cout << "move "
       << columns[move.source().column()]
       << rows[move.source().row()]
       << columns[move.destination().column()]
       << rows[move.destination().row()];
  if (move.is_conversion()) {
    if (move.created_piece() == PieceSet::instance().bishop()->piece_index()) {
      cout << "b";
    } else if (move.created_piece() == PieceSet::instance().knight()->piece_index()) {
      cout << "n";
    } else if (move.created_piece() == PieceSet::instance().queen()->piece_index()) {
      cout << "q";
    } else if (move.created_piece() == PieceSet::instance().rook()->piece_index()) {
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

void tell_opponent(const std::string &message)
{
  cout << "tellopponent " << message << endl;
}

void tell_others(const std::string &message)
{
  cout << "tellothers " << message << endl;
}

void tell_all(const std::string &message)
{
  cout << "tellall " << message << endl;
}

void tell_user(const std::string &message)
{
  cout << "telluser " << message << endl;
}

void tell_user_error(const std::string &message)
{
  cout << "tellusererror " << message << endl;
}

void askuser(const std::string &rep_tag, const std::string &question)
{
  cout << "askuser " << rep_tag << " " << question << endl;
}

void tell_ics(const std::string &message)
{
  cout << "tellics " << message << endl;
}

void tell_ics_noalias(const std::string &message)
{
  cout << "tellicsnoalias " << message << endl;
}

void comment(const std::string &message)
{
  cout << "# " << message << endl;
}

void pong(const std::string& number)
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
