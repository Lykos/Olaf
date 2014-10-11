#include <QString>
#include <QtTest>

class OlafEvaluationTest : public QObject
{
  Q_OBJECT

public:
  OlafEvaluationTest();

private Q_SLOTS:
  void testCase1();
};

OlafEvaluationTest::OlafEvaluationTest()
{
}

void OlafEvaluationTest::testCase1()
{
  QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(OlafEvaluationTest)

#include "tst_olafevaluationtest.moc"
