#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace olaf
{

class Status
{
public:
  static Status error(const std::string& message);

  static Status valid();

  const std::string& message() const;

  bool ok() const;

private:
  Status(const bool ok, const std::string& message);

  std::string m_message;

  bool m_ok;
};

} // namespace olaf

#endif // CONFIG_H
