#ifndef COMPOSITEPERFORMANCERESULT_H
#define COMPOSITEPERFORMANCERESULT_H

#include <vector>
#include <string>
#include <chrono>
#include <ostream>
#include <sstream>

#include "benchmarkresult.h"

using namespace std;

template <typename T>
class CompositeBenchmarkResult;

template <typename T>
ostream& operator<<(ostream& out, const CompositeBenchmarkResult<T>& result);

template <typename T>
class CompositeBenchmarkResult : public BenchmarkResult
{
  friend ostream& operator<< <> (ostream& out,
                                 const CompositeBenchmarkResult<T>& result);

public:
  CompositeBenchmarkResult();

  explicit CompositeBenchmarkResult(const string& description);

  const vector<T>& get_sub_results() const;

  void add_sub_result(const T& sub_result);

private:
  vector<T> m_sub_results;
};

template <typename T>
CompositeBenchmarkResult<T>::CompositeBenchmarkResult(const string& description):
  BenchmarkResult(description)
{}

template <typename T>
const vector<T>& CompositeBenchmarkResult<T>::get_sub_results() const
{
  return m_sub_results;
}

template <typename T>
void CompositeBenchmarkResult<T>::add_sub_result(const T& sub_result)
{
  m_sub_results.push_back(sub_result);
  if (sub_result.has_score()) {
    m_has_score = true;
    m_score += sub_result.score();
  }
  if (sub_result.has_millis()) {
    m_has_millis = true;
    m_millis += sub_result.millis();
  }
}

template <typename T>
ostream& operator <<(ostream& out,
                     const CompositeBenchmarkResult<T>& result)
{
  out << result.m_description << ":" << endl;
  for (const T& sub_result : result.m_sub_results) {
    stringstream ss;
    ss << sub_result;
    string line;
    while (getline(ss, line)) {
      out << BenchmarkResult::c_indentation << line << endl;
    }
  }
  if (result.m_has_millis) {
    out << "total time: " << result.m_millis.count() << " ms" << endl;
  }
  if (result.m_has_score) {
    out << "total score: " << result.m_score << endl;
  }
  return out;
}

#endif // COMPOSITEPERFORMANCERESULT_H
