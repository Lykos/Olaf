#include "autotest.h"

#include <algorithm>
#include <string>
#include <QTest>

namespace auto_test {

TestList& test_list()
{
  static TestList list;
  return list;
}

bool find_test(QObject* const test)
{
  TestList& list = test_list();
  if (find(list.begin(), list.end(), test) != list.end()) {
    return true;
  }
  for (QObject* const test2 : list) {
    if (test2->objectName() == test->objectName()) {
      return true;
    }
  }
  return false;
}

void add_test(QObject* const test)
{
  TestList& list = test_list();
  if (!find_test(test)) {
    list.push_back(test);
  }
}

int run(int argc, char *argv[])
{
  int ret = 0;
  for (QObject* const test : test_list()) {
    ret += QTest::qExec(test, argc, argv);
  }
  return ret;
}
} // namespace auto_test
