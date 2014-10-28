#include "autotest.h"
#include <gflags/gflags.h>

int main(int argc, char* argv[])
{
  google::ParseCommandLineFlags(&argc, &argv, true);
  return ::olaf::test::auto_test::run(argc, argv);
}
