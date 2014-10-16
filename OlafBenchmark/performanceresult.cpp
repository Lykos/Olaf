#include "performanceresult.h"

#include <chrono>
#include <string>

using namespace std;
using namespace chrono;

BenchmarkResult::BenchmarkResult(const string& description,
                                 const long score):
  m_description(description),
  m_score(score),
  m_has_score(true)
{}

BenchmarkResult::BenchmarkResult(const string& description,
                                 const milliseconds& millis):
  m_description(description),
  m_millis(millis),
  m_has_millis(true)
{}

const string& BenchmarkResult::description() const
{
  return m_description;
}

const milliseconds& BenchmarkResult::millis() const
{
  return m_millis;
}

bool BenchmarkResult::has_millis() const
{
  return m_has_millis;
}

long BenchmarkResult::score() const
{
  return m_score;
}

bool BenchmarkResult::has_score() const
{
  return m_has_score;
}

ostream& operator<<(ostream& out, const BenchmarkResult& result)
{
  out << result.m_description;
  for (unsigned int i = result.m_description.size(); i < BenchmarkResult::c_description_size; ++i) {
    out << " ";
  }
  if (result.m_has_millis) {
    out << " time: " << result.m_millis.count() << " ms";
  }
  if (result.m_has_score) {
    out << " score: " << result.m_score;
  }
  return out;
}

bool operator <(const BenchmarkResult& a, const BenchmarkResult& b)
{
  if (a.m_has_millis && b.m_has_millis && a.m_millis < b.m_millis) {
    return true;
  }
  if (a.m_has_score && b.m_has_score && a.m_score < b.m_score) {
    return true;
  }
  return false;
}

const unsigned int BenchmarkResult::c_description_size(20);
