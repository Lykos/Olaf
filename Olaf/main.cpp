#include <iostream>
#include "xboardreader.h"

using namespace std;

int main()
{
  cout.setf(ios::unitbuf);
  string protocol_name;
  getline(cin, protocol_name);
  if (protocol_name == "xboard") {
    XBoardReader().run();
  } else {
    cout << "Error: Unknown protocol " << protocol_name << "." << endl;
    return 1;
  }
  return 0;
}
