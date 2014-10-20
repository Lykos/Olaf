#ifndef AUTOTEST_H
#define AUTOTEST_H

#include <QTest>
#include <QList>
#include <string>
#include <memory>

namespace auto_test
{
typedef std::vector<QObject*> TestList;

TestList& test_list();

bool find_test(QObject* test);

void add_test(QObject* test);

int run(int argc, char* argv[]);

template <class T>
struct TestHolder
{
  std::unique_ptr<T> child;

  TestHolder(const char* const name):
    child(new T)
  {
    child->setObjectName(name);
    auto_test::add_test(child.get());
  }
};

} // namespace auto_test

#define DECLARE_TEST(className) static ::auto_test::TestHolder<className> t(#className);

#define AUTOTEST_MAIN \
  int main(int argc, char *argv[]) \
  { \
      return ::auto_test::run(argc, argv); \
  }

#endif // AUTOTEST_H
