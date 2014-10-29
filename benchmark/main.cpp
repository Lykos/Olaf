#include <cstdlib>
#include <QtTest/QTest>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <gflags/gflags.h>

#include "autobenchmark.h"
#include "compositebenchmarkresult.h"
#include "benchmarkresult.h"
#include "olaf/config.h"

using namespace std;
using namespace olaf;
using namespace benchmark;

DEFINE_string(config_file, "/usr/local/share/olaf/config.yml", "Config file for the engine.");

Config read_config(const string& config_file)
{
  std::ifstream file(config_file.c_str());
  std::string config_string((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
  return Config(config_string);
}

int main(int argc, char* argv[])
{
  google::ParseCommandLineFlags(&argc, &argv, true);

  // get hostname
  char hostname[1024];
  hostname[1023] = '\0';
  gethostname(hostname, 1023);

  // get time
  struct tm * timeinfo;
  time_t rawtime;
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  // File name
  string version_name = VERSION_NAME;
  ostringstream oss2;
  oss2 << "../../Olaf/performance_results/" << version_name << "_" << VERSION << "_" << hostname << "_" << (1900 + timeinfo->tm_year) << "-" << timeinfo->tm_mon << "-"
      << timeinfo->tm_mday << "_" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec;
  string file_name = oss2.str();
  cout << "Writing results to " << file_name << endl;

  // description
  ostringstream oss;
  oss << version_name << " " << VERSION << " " << hostname << " " << (1900 + timeinfo->tm_year) << "-" << timeinfo->tm_mon << "-"
      << timeinfo->tm_mday << " " << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec;
  string description = oss.str();

  Config config = read_config(FLAGS_config_file);
  const auto_benchmark::GlobalResult& global_result =
      auto_benchmark::run(argc, argv, description, &config);

  // Write result to file
  ofstream result_file(file_name.c_str());
  result_file << global_result;
  cout << global_result;

  return EXIT_SUCCESS;
}
