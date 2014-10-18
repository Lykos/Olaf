#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <yaml-cpp/yaml.h>

class Config
{
public:
  explicit Config(const std::string& config);

private:
  const YAML::Node m_config;
};

#endif // CONFIG_H
