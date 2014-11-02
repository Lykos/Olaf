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

} // namespace olaf
