#include <memory>
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <gflags/gflags.h>

#include "OlafSearching/searcherfactory.h"
#include "OlafProtocols/protocolreader.h"
#include "OlafProtocols/protocolwriter.h"
#include "OlafProtocols/xboardreader.h"
#include "OlafProtocols/xboardwriter.h"
#include "OlafProtocols/engine.h"
#include "OlafProtocols/engineeventhelper.h"
#include "OlafProtocols/simplethinkingwriter.h"
#include "OlafSearching/thinkingwriter.h"

using namespace std;

DEFINE_string(input_file, "", "If this is non-empty, the input will be read from here instead of stdin.");

DEFINE_string(output_file, "", "If this is non-empty, the output will be written here instead of stdout.");

int main(int argc, char* argv[])
{
  google::ParseCommandLineFlags(&argc, &argv, true);
  istream* in;
  std::unique_ptr<ifstream> in_file_deleter;
  ostream* out;
  std::unique_ptr<ofstream> out_file_deleter;
  if (!FLAGS_input_file.empty()) {
    in_file_deleter.reset(new ifstream(FLAGS_input_file, fstream::in));
    in = in_file_deleter.get();
  } else {
    in = &cin;
  }
  if (!FLAGS_output_file.empty()) {
    out_file_deleter.reset(new ofstream(FLAGS_output_file, fstream::out));
    out = out_file_deleter.get();
  } else {
    out = &cout;
  }
  out->setf(ios::unitbuf);
  string protocol_name;
  getline(*in, protocol_name);
  unique_ptr<ProtocolWriter> writer;
  if (protocol_name == "xboard") {
    writer.reset(new XBoardWriter(out));
  } else {
    *out << "Error: Unknown protocol " << protocol_name << "." << endl;
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
    reader.reset(new XBoardReader(static_cast<XBoardWriter*>(writer.get()), move(engine_helper), in));
  }
  thread engine_thread ([&engine] { engine.run(); });
  thread reader_thread ([&reader] { reader->run(); });
  engine_thread.join();
  reader_thread.join();
  return 0;
}
