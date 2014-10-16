#ifndef PERFORMANCERESULT_H
#define PERFORMANCERESULT_H

#include <ostream>

class BenchmarkResult;

std::ostream& operator<<(std::ostream& out, const BenchmarkResult& result);

struct CompareMillis
{
  bool operator()(const BenchmarkResult& a, const BenchmarkResult& b) const;
};

class BenchmarkResult {
  friend std::ostream& operator<<(std::ostream& out, const BenchmarkResult& result);

  friend CompareMillis;

public:
  BenchmarkResult(const BenchmarkResult& other);

  BenchmarkResult(BenchmarkResult&& other);

  BenchmarkResult& operator=(const BenchmarkResult& other);

  BenchmarkResult& operator=(BenchmarkResult&& other);

  ~BenchmarkResult();

  BenchmarkResult(const std::string& description,
                  long milliseconds,
                  long score = 0);

  const std::string& description() const;

  long milliseconds() const;

private:
  std::string m_description;

  long m_milliseconds;

  long m_score;

  static const unsigned int c_description_size;

};

#endif // PERFORMANCERESULT_H
