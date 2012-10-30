#include <iostream>
#include "xboardprotocol.h"
#include "uciprotocol.h"

using namespace std;

int main()
{
  cout.setf(ios::unitbuf);
  string protocol_name;
  cin >> protocol_name;
  if (protocol_name == XBoardProtocol::name()) {

  } else if (protocol_name == UCIProtocol::name()) {
  } else {
    cout << "Error: Unknown protocol " << protocol_name << "." << endl;
    return 1;
  }
  return 0;
}
