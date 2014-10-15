#include "performanceresult.h"
#include <cstring>

PerformanceResult::PerformanceResult(const PerformanceResult& other):
  m_description (other.m_description),
  m_milliseconds (other.m_milliseconds)
{}

PerformanceResult::PerformanceResult(PerformanceResult&& other):
  m_description (std::move(other.m_description)),
  m_milliseconds (other.m_milliseconds)
{}

PerformanceResult& PerformanceResult::operator=(const PerformanceResult& other)
{
  m_description = other.m_description;
  m_milliseconds = other.m_milliseconds;
  return *this;
}

PerformanceResult& PerformanceResult::operator=(PerformanceResult&& other)
{
  m_description = std::move(other.m_description);
  m_milliseconds = other.m_milliseconds;
  return *this;
}

PerformanceResult::~PerformanceResult()
{}

PerformanceResult::PerformanceResult(const std::string& description,
                                     const long milliseconds):
  m_description (description),
  m_milliseconds (milliseconds)
{
}

const std::string& PerformanceResult::description() const
{
  return m_description;
}

long PerformanceResult::milliseconds() const
{
  return m_milliseconds;
}

std::ostream& operator<<(std::ostream& out, const PerformanceResult& result)
{
  out << result.m_description;
  for (unsigned int i = result.m_description.size(); i < PerformanceResult::c_description_size; ++i) {
    out << " ";
  }
  return out << " " << result.m_milliseconds << " ms";
}

bool CompareMillis::operator()(const PerformanceResult& a, const PerformanceResult& b) const
{
  return a.m_milliseconds < b.m_milliseconds;
}

const unsigned int PerformanceResult::c_description_size(20);
