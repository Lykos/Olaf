#ifndef PERFORMANCERESULT_H
#define PERFORMANCERESULT_H

#include <ostream>
#include <chrono>
#include <string>

class BenchmarkResult;

std::ostream& operator<<(std::ostream& out, const BenchmarkResult& result);

bool operator <(const BenchmarkResult& left, const BenchmarkResult& right);

class BenchmarkResult {
  friend std::ostream& operator<<(std::ostream& out, const BenchmarkResult& result);

  friend bool operator <(const BenchmarkResult& left, const BenchmarkResult& right);

public:
  BenchmarkResult(const std::string& description,
                  const std::chrono::milliseconds& millis);

  BenchmarkResult(const std::string& description,
                  long score);

  long score() const;

  bool has_score() const;

  const std::string& description() const;

  const std::chrono::milliseconds& millis() const;

  bool has_millis() const;

protected:
  std::string m_description;

  std::chrono::milliseconds m_millis;

  bool m_has_millis = false;

  long m_score;

  bool m_has_score = false;

  static const unsigned int c_description_size;

};

#endif // PERFORMANCERESULT_H
