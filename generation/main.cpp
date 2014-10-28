#include <gflags/gflags.h>

#include "generation.h"

using namespace std;

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  olaf::generation::generate_magic();
  return 0;
}
