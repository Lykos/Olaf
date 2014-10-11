#include "OlafSearching/searcherfactory.h"
#include "OlafProtocols/protocolreader.h"
#include "OlafProtocols/protocolwriter.h"
#include "OlafProtocols/xboardreader.h"
#include "OlafProtocols/xboardwriter.h"
#include "OlafProtocols/engine.h"
#include "OlafProtocols/engineeventhelper.h"
#include "OlafProtocols/simplethinkingwriter.h"
#include "OlafSearching/thinkingwriter.h"
#include <memory>
#include <iostream>

using namespace std;

int main()
{
  cout.setf(ios::unitbuf);
  string protocol_name;
  getline(cin, protocol_name);
  unique_ptr<ProtocolWriter> writer;
  if (protocol_name == "xboard") {
    writer.reset(new XBoardWriter);
  } else {
    cout << "Error: Unknown protocol " << protocol_name << "." << endl;
    return 1;
  }
  SimpleThinkingWriter thinking_writer(writer.get());
  SearcherFactory factory(&thinking_writer);
  auto searcher = factory.timed_searcher();
  BoardState board_state(factory.move_creator());
  unique_ptr<ProtocolReader> reader;
  Engine engine(writer.get(), &board_state, move(searcher));
  std::unique_ptr<EngineEventHelper> engine_helper(
        new EngineEventHelper(writer.get(), &board_state, &engine, &thinking_writer));
  if (protocol_name == "xboard") {
    reader.reset(new XBoardReader(static_cast<XBoardWriter*>(writer.get()), move(engine_helper)));
  }
  thread engine_thread ([&engine] { engine.run(); });
  thread reader_thread ([&reader] { reader->run(); });
  engine_thread.join();
  reader_thread.join();
  return 0;
}
