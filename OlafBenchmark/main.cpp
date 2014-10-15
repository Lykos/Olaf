#include <cstdlib>
#include <QtTest/QTest>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "autobenchmark.h"
#include "compositeperformanceresult.h"
#include "performanceresult.h"

using namespace std;

int main(int argc, char *argv[])
{
  // get hostname
  char hostname[1024];
  hostname[1023] = '\0';
  gethostname(hostname, 1023);

  // get time
  struct tm * timeinfo;
  time_t rawtime;
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  // description
  string version_name ("Benchmark_new_unbalanced_strategy");
  ostringstream oss;
  oss << version_name << " " << hostname << " " << (1900 + timeinfo->tm_year) << "-" << timeinfo->tm_mon << "-"
      << timeinfo->tm_mday << " " << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << endl;
  string description = oss.str();

  const auto_benchmark::GlobalResult& global_result =
      auto_benchmark::run(argc, argv, description);

  // Write result to file
  ostringstream oss2;
  oss2 << "../../Olaf/performance_results/" << version_name << "_" << hostname << "_" << (1900 + timeinfo->tm_year) << "-" << timeinfo->tm_mon << "-"
      << timeinfo->tm_mday << "_" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec;
  string file_name = oss2.str();
  ofstream result_file(file_name.c_str());
  result_file << global_result;
  cout << global_result;

  return EXIT_SUCCESS;
}