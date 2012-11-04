#include "OlafSearching/searcherfactory.h"
#include "OlafProtocols/protocolreader.h"
#include "OlafProtocols/protocolwriter.h"
#include "OlafProtocols/xboardreader.h"
#include "OlafProtocols/xboardwriter.h"
#include "OlafProtocols/engineconsumer.h"
#include "OlafProtocols/engineproducer.h"
#include <memory>
#include <iostream>

using namespace std;

int main()
{
  cout.setf(ios::unitbuf);
  string protocol_name;
  getline(cin, protocol_name);
  shared_ptr<ProtocolWriter> writer;
  shared_ptr<XBoardWriter> xboard_writer;
  if (protocol_name == "xboard") {
    shared_ptr<XBoardWriter> tmp (new XBoardWriter());
    xboard_writer = tmp;
    writer = static_pointer_cast<ProtocolWriter>(xboard_writer);
  } else {
    cout << "Error: Unknown protocol " << protocol_name << "." << endl;
    return 1;
  }
  SearcherFactory factory;
  auto searcher = factory.timed_searcher();
  shared_ptr<BoardState> board_state (new BoardState(factory.move_creator()));
  shared_ptr<ProtocolReader> reader;
  shared_ptr<EngineConsumer> consumer (new EngineConsumer(writer, board_state, searcher));
  shared_ptr<EngineProducer> producer (new EngineProducer(writer, board_state, consumer));
  if (protocol_name == "xboard") {
    shared_ptr<ProtocolReader> xboard_reader (new XBoardReader(xboard_writer, producer));
    reader = xboard_reader;
  }
  thread consumer_thread ([consumer] { consumer->run(); });
  reader->run();
  consumer_thread.join();
  return 0;
}
