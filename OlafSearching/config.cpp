#include "config.h"

#include <string>
#include <yaml-cpp/yaml.h>

Config::Config(const std::string& config):
  m_config(YAML::Load(config))
{}
