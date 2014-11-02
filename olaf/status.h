#ifndef STATUS_H
#define STATUS_H

#include <string>
#include <ostream>

namespace olaf
{

class Status;

std::ostream& operator <<(std::ostream& out, const Status& status);

bool operator ==(const Status& left, const Status& right);

class Status
{
  friend std::ostream& operator <<(std::ostream& out, const Status& status);

  friend bool operator ==(const Status& left, const Status& right);

public:
  static Status error(const std::string& message);

  static Status valid();

  const std::string& message() const;

  bool ok() const;

private:
  Status(bool ok, const std::string& message);

  std::string m_message;

  bool m_ok;
};

} // namespace olaf

#endif // STATUS_H
