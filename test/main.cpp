#include <gflags/gflags.h>

#include "test/autotest.h"
#include "olaf/rules/magicnumbers.h"

int main(int argc, char* argv[])
{
  google::ParseCommandLineFlags(&argc, &argv, true);
  olaf::MagicNumbers::init();
  return ::olaf::test::auto_test::run(argc, argv);
}
