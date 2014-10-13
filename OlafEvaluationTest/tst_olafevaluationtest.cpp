#include "materialevaluatortest.h"
#include <QtTest>

int main(int argc, char **argv)
{
  MaterialEvaluatorTest material_evaluator_test;
  QTest::qExec(&material_evaluator_test, argc, argv);
  return 0;
}
