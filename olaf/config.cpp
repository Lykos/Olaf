#include "config.h"

#include <string>
#include <yaml-cpp/yaml.h>

namespace olaf
{

Config::Config(const std::string& config):
  m_config(YAML::Load(config))
{}

} // namespace olaf
