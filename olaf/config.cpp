#include "config.h"

#include <string>
#include <yaml-cpp/yaml.h>

namespace olaf
{

Config::Config(const std::string& config):
  m_config(YAML::Load(config)),
  m_evaluation(m_config["evaluation"]),
  m_search(m_config["search"]),
  m_transposition_table(m_config["transposition_table"]),
  m_move_ordering(m_config["move_ordering"])
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

bool Config::MoveOrdering::use_hash_move() const
{
  return m_node["use_hash_move"].as<bool>();
}

bool Config::MoveOrdering::use_see() const
{
  return m_node["use_see"].as<bool>();
}

bool Config::MoveOrdering::use_killers() const
{
  return m_node["use_killers"].as<bool>();
}

} // namespace olaf
