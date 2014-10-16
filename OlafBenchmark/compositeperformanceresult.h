#ifndef COMPOSITEPERFORMANCERESULT_H
#define COMPOSITEPERFORMANCERESULT_H

#include <vector>
#include <string>
#include <chrono>
#include <ostream>
#include <sstream>

using namespace std;

template <typename T>
class CompositeBenchmarkResult;

template <typename T>
ostream& operator<<(ostream& out, const CompositeBenchmarkResult<T>& result);

const char c_indentation[] = "\t";

template <typename T>
class CompositeBenchmarkResult
{
  friend ostream& operator<< <> (ostream& out,
                                 const CompositeBenchmarkResult<T>& result);

public:
  CompositeBenchmarkResult();

  explicit CompositeBenchmarkResult(const string& description);

  const string& description() const;

  const vector<T>& get_sub_results() const;

  void add_sub_result(const T& sub_result);

  const std::chrono::milliseconds& millis() const;

  bool has_millis() const;

  long score() const;

  bool has_score() const;

private:
  string m_description;

  vector<T> m_sub_results;

  std::chrono::milliseconds m_millis;

  bool m_has_millis = false;

  long m_score = 0;

  bool m_has_score = false;
};

template <typename T>
CompositeBenchmarkResult<T>::CompositeBenchmarkResult(const string& description):
  m_description(description),
  m_millis(0)
{}

template <typename T>
const string& CompositeBenchmarkResult<T>::description() const
{
  return m_description;
}

template <typename T>
const vector<T>& CompositeBenchmarkResult<T>::get_sub_results() const
{
  return m_sub_results;
}

template <typename T>
const std::chrono::milliseconds& CompositeBenchmarkResult<T>::millis() const
{
  return m_millis;
}

template <typename T>
bool CompositeBenchmarkResult<T>::has_millis() const
{
  return m_has_millis;
}

template <typename T>
long CompositeBenchmarkResult<T>::score() const
{
  return m_score;
}

template <typename T>
bool CompositeBenchmarkResult<T>::has_score() const
{
  return m_has_score;
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
ostream& operator<<(ostream& out,
                    const CompositeBenchmarkResult<T>& result)
{
  out << result.m_description << endl;
  for (const T& sub_result : result.m_sub_results) {
    stringstream ss;
    ss << sub_result;
    string line;
    while (getline(ss, line)) {
      out << c_indentation << line << endl;
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
