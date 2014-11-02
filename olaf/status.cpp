#include "status.h"

#include <string>

namespace olaf
{

// static
Status Status::error(const std::string& message)
{
  return Status(false, message);
}

// static
Status Status::valid()
{
  static const Status c_valid(true, "");
  return c_valid;
}

const std::string& Status::message() const
{
  return m_message;
}

bool Status::ok() const
{
  return m_ok;
}

Status::Status(const bool ok, const std::string& message):
  m_message(message),
  m_ok(ok)
{}

std::ostream& operator <<(std::ostream& out, const Status& status)
{
  if (status.m_ok) {
    out << "OK";
  } else {
    out << "ERROR(" << status.m_message << ")";
  }
  return out;
}

bool operator ==(const Status& left, const Status& right)
{
  return left.m_ok == right.m_ok && left.m_message == right.m_message;
}

} // namespace olaf
