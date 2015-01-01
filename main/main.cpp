#include <memory>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <istream>
#include <ostream>
#include <gflags/gflags.h>

#include "generation/generation.h"
#include "olaf/rules/magicnumbers.h"
#include "olaf/search/searcherfactory.h"
#include "protocols/protocolreader.h"
#include "protocols/protocolwriter.h"
#include "protocols/xboardreader.h"
#include "protocols/xboardwriter.h"
#include "protocols/engine.h"
#include "protocols/engineeventhelper.h"
#include "protocols/simplethinkingwriter.h"
#include "olaf/search/thinkingwriter.h"

using namespace std;
using namespace olaf;

DEFINE_string(input_file, "", "If this is non-empty, the input will be read from here instead of stdin.");

DEFINE_string(output_file, "", "If this is non-empty, the output will be written here instead of stdout.");

DEFINE_string(config_file, "/usr/local/share/olaf/config.yml", "Config file for the engine.");

Config read_config(const string& config_file)
{
  ifstream file(config_file.c_str(), ios::in);
  if (!file.good()) {
    cout << "Unable to read config file " << FLAGS_config_file << ". Please specify one with --config_file=/path/to/file." << endl;
    file.close();
    exit(1);
  }
  string config_string((istreambuf_iterator<char>(file)),
                        istreambuf_iterator<char>());
  file.close();
  return Config(config_string);
}

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

  // If the move table doesn't exist, generate it.
  {
    ifstream move_table(FLAGS_move_table_file.c_str());
    const int size = move_table.tellg();
    if (size != sizeof(MagicNumbers::MoveTable)) {
      const Status& status = generation::generate_magic(FLAGS_move_table_file, false);
      if (!status.ok()) {
        cout << status.message() << endl
             << "Move table does not exist and generating it failed." << endl
             << "In order to generate the move table at a different place," << endl
             << "specify a path using --move_table=path/to/file." << endl;
        exit(1);
      }
    }
    move_table.close();
  }

  // Decide which protocol to use.
  string protocol_name;
  getline(*in, protocol_name);
  unique_ptr<ProtocolWriter> writer;
  if (protocol_name == "xboard") {
    writer.reset(new XBoardWriter(out));
  } else {
    *out << "Error: Unknown protocol " << protocol_name << "." << endl;
    return 1;
  }

  // Create engine.
  SimpleThinkingWriter thinking_writer(writer.get());
  const Config config = read_config(FLAGS_config_file);
  SearcherFactory factory(&thinking_writer, &config);
  auto searcher = factory.timed_searcher();
  BoardState board_state;
  unique_ptr<ProtocolReader> reader;
  Engine engine(writer.get(),
                factory.transposition_table(),
                factory.pawn_table(),
                factory.egbb_prober(),
                &board_state,
                move(searcher));
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
