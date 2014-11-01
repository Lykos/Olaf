#include "config.h"

#include <string>
#include <yaml-cpp/yaml.h>

namespace olaf
{

Config::Config(const std::string& config):
  m_config(YAML::Load(config)),
  m_evaluation(),
  m_search(m_config["search"]),
  m_transposition_table(m_config["transposition_table"]),
  m_move_ordering(m_config["move_ordering"])
{}

Config::Search::Search(const YAML::Node& node):
  m_time_millis(node["time_millis"].as<int>()),
  m_min_depth(node["min_depth"].as<int>()),
  m_sequential_depth(node["sequential_depth"].as<int>()),
  m_use_quiescent_search(node["use_quiescent_search"])
{}

Config::TranspositionTable::TranspositionTable(const YAML::Node& node):
  m_size(node["size"].as<int>())
{}

Config::MoveOrdering::MoveOrdering(const YAML::Node& node):
  m_use_hash_move(node["use_hash_move"].as<bool>()),
  m_use_see(node["use_see"].as<bool>()),
  m_use_killers(node["use_killers"].as<bool>())
{}

} // namespace olaf
