#ifndef EGBBPROBERTEST_H
#define EGBBPROBERTEST_H

#include <QObject>
#include <memory>

#include "test/autotest.h"

namespace olaf
{
namespace test
{

class EgbbProberTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_no_so();

  void test_wrong_so();

  void test_wrong_path();

  void test_probe_without_load();

  void test_probe_for_unknown();

  void test_probe_draw();

  void test_probe_win();
};

DECLARE_TEST(EgbbProberTest)

} // namespace test
} // namespace olaf

#endif // EGBBPROBERTEST_H
