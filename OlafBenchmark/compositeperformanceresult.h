#ifndef COMPOSITEPERFORMANCERESULT_H
#define COMPOSITEPERFORMANCERESULT_H

#include <vector>
#include <string>
#include <ostream>
#include <sstream>

using namespace std;

template <typename T>
class CompositePerformanceResult;

template <typename T>
ostream& operator<<(ostream& out, const CompositePerformanceResult<T>& result);

const char c_indentation[] = "\t";

template <typename T>
class CompositePerformanceResult
{
  friend ostream& operator<< <> (ostream& out,
                                 const CompositePerformanceResult<T>& result);

public:
  CompositePerformanceResult();

  explicit CompositePerformanceResult(const string& description);

  const string& description() const;

  const vector<T>& get_sub_results() const;

  void add_sub_result(const T& sub_result);

  long score() const;

  bool has_score() const;

private:
  string m_description;

  vector<T> m_sub_results;

  bool m_has_score = false;

  long m_score = 0;

};

template <typename T>
CompositePerformanceResult<T>::CompositePerformanceResult(const string& description):
  m_description(description)
{}

template <typename T>
const string& CompositePerformanceResult<T>::description() const
{
  return m_description;
}

template <typename T>
const vector<T>& CompositePerformanceResult<T>::get_sub_results() const
{
  return m_sub_results;
}

template <typename T>
bool CompositePerformanceResult<T>::has_score() const
{
  return m_has_score;
}

static const long c_no_score = -1;

template <typename T>
long CompositePerformanceResult<T>::score() const
{
  return m_has_score ? m_score : c_no_score;
}

template <typename T>
void CompositePerformanceResult<T>::add_sub_result(const T& sub_result)
{
  m_sub_results.push_back(sub_result);
  if (sub_result.has_score()) {
    m_has_score = true;
    m_score += sub_result.score();
  }
}

template <typename T>
ostream& operator<<(ostream& out,
                    const CompositePerformanceResult<T>& result)
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
  if (result.m_has_score) {
    out << "total score: " << result.m_score;
  }
  return out;
}

#endif // COMPOSITEPERFORMANCERESULT_H
