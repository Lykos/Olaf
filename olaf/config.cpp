#include "config.h"

#include <string>
#include <yaml-cpp/yaml.h>

namespace olaf
{

Config::Config(const std::string& config):
  m_config(YAML::Load(config)),
  m_evaluation(m_config["evaluation"]),
  m_search(m_config["search"]),
  m_transposition_table(m_config["transposition_table"])
{}

Config::ConfigSection::ConfigSection(const YAML::Node& node):
  m_node(node)
{}

} // namespace olaf
