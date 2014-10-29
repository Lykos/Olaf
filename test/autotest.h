#ifndef AUTOTEST_H
#define AUTOTEST_H

#include <QTest>
#include <QList>
#include <string>
#include <memory>

namespace olaf
{
namespace test
{
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
} // namespace test
} // namespace olaf

#define DECLARE_TEST(className) static ::olaf::test::auto_test::TestHolder<className> t(#className);

#endif // AUTOTEST_H
