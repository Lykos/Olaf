#include "xboardprotocol.h"
#include <sstream>

using namespace std;

XBoardProtocol::XBoardProtocol():
  m_board (create_initial_board())
{}

void XBoardProtocol::run()
{
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
      return;
    default:
      if (is_move(message)) {
        handle_move(message);
      } else {
        unknown_command(message);
      }
    }
  }
}

static const string columns = "abcdefgh";
static const string rows = "012345678";
static const string conversions = "rbnq";

bool is_move(const std::string& command) const
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

void handle_move(const std::string&) const
{

}

void XBoardProtocol::write_features() const
{
  cout << "done=0" << endl;
  cout << "feature ";
  cout << "ping=1 ";
  cout << "setboard=1 ";
  cout << "usermove=1 ";
  cout << "myname=\"Olaf\" ";
  cout << "variants=\"normal\" ";
  cout << "colors=0 ";
  cout << "ics=1 ";
  cout << "name=1 ";
  cout << "pause=1 ";
  cout << "nps=0 ";
  cout << "done=1" << endl;
}

void XBoardProtocol::unknown_command(const string &command) const
{
  cout << "Error (unknown command): " << command;
}

const string& XBoardProtocol::name()
{
  return "xboard";
}
