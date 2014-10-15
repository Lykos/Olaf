#ifndef PERFORMANCERESULT_H
#define PERFORMANCERESULT_H

#include <ostream>

class PerformanceResult;

std::ostream& operator<<(std::ostream& out, const PerformanceResult& result);

struct CompareMillis
{
  bool operator()(const PerformanceResult& a, const PerformanceResult& b) const;
};

class PerformanceResult {
  friend std::ostream& operator<<(std::ostream& out, const PerformanceResult& result);

  friend CompareMillis;

public:
  PerformanceResult(const PerformanceResult& other);

  PerformanceResult(PerformanceResult&& other);

  PerformanceResult& operator=(const PerformanceResult& other);

  PerformanceResult& operator=(PerformanceResult&& other);

  ~PerformanceResult();

  PerformanceResult(const std::string& description,
                    long milliseconds);

  const std::string& description() const;

  long milliseconds() const;

private:
  std::string m_description;

  long m_milliseconds;

  static const unsigned int c_description_size;

};

#endif // PERFORMANCERESULT_H
