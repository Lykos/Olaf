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

long Config::Search::time_millis() const
{
  return m_node["time_millis"].as<long>();
}

int Config::Search::min_depth() const
{
  return m_node["min_depth"].as<int>();
}

int Config::Search::sequential_depth() const
{
  return m_node["sequential_depth"].as<int>();
}


long Config::TranspositionTable::size() const
{
  return m_node["size"].as<int>();
}

} // namespace olaf
