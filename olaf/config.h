#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <yaml-cpp/yaml.h>

namespace olaf
{

class Config
{
public:
  explicit Config(const std::string& config);

private:
  const YAML::Node m_config;
};

} // namespace olaf

#endif // CONFIG_H
