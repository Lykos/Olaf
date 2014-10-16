#include "performanceresult.h"
#include <cstring>

BenchmarkResult::BenchmarkResult(const BenchmarkResult& other):
  m_description (other.m_description),
  m_milliseconds (other.m_milliseconds)
{}

BenchmarkResult::BenchmarkResult(BenchmarkResult&& other):
  m_description (std::move(other.m_description)),
  m_milliseconds (other.m_milliseconds)
{}

BenchmarkResult& BenchmarkResult::operator=(const BenchmarkResult& other)
{
  m_description = other.m_description;
  m_milliseconds = other.m_milliseconds;
  return *this;
}

BenchmarkResult& BenchmarkResult::operator=(BenchmarkResult&& other)
{
  m_description = std::move(other.m_description);
  m_milliseconds = other.m_milliseconds;
  return *this;
}

BenchmarkResult::~BenchmarkResult()
{}

BenchmarkResult::BenchmarkResult(const std::string& description,
                                 const long milliseconds,
                                 const long score):
  m_description(description),
  m_milliseconds(milliseconds),
  m_score(score)
{}

const std::string& BenchmarkResult::description() const
{
  return m_description;
}

long BenchmarkResult::milliseconds() const
{
  return m_milliseconds;
}

void BenchmarkResult::score(const long score)
{
  m_score = score;
  m_has_score = true;
}

static const long c_no_score = -1;

long BenchmarkResult::score() const
{
  return m_has_score ? m_score : c_no_score;
}

std::ostream& operator<<(std::ostream& out, const BenchmarkResult& result)
{
  out << result.m_description;
  for (unsigned int i = result.m_description.size(); i < BenchmarkResult::c_description_size; ++i) {
    out << " ";
  }
  return out << " " << result.m_milliseconds << " ms";
}

bool CompareMillis::operator()(const BenchmarkResult& a, const BenchmarkResult& b) const
{
  return a.m_milliseconds < b.m_milliseconds;
}

const unsigned int BenchmarkResult::c_description_size(20);
