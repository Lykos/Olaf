#include "config.h"

#include <string>
#include <yaml-cpp/yaml.h>

using namespace std;

namespace olaf
{

template <typename T>
static T find_with_default(const YAML::Node& node, const string& name, const T& defaut) {
  if (node) {
    return node[name].as<T>(defaut);
  } else {
    return defaut;
  }
}

Config::Config(const std::string& config):
  m_config(YAML::Load(config)),
  m_evaluation(),
  m_search(m_config["search"]),
  m_transposition_table(m_config["transposition_table"]),
  m_tablebases(m_config["tablebases"]),
  m_move_ordering(m_config["move_ordering"])
{}

Config::Config():
  Config("")
{}

Config::Search::Search(const YAML::Node& node):
  m_default_moves_to_play(find_with_default(node, "default_moves_to_play", 40)),
  m_min_depth(find_with_default(node, "min_depth", 1)),
  m_sequential_depth(find_with_default(node, "sequential_depth", 2)),
  m_use_quiescent_search(find_with_default(node, "use_quiescent_search", true)),
  m_initial_window(find_with_default(node, "initial_window", 25))
{}

Config::TranspositionTable::TranspositionTable(const YAML::Node& node):
  m_size(find_with_default(node, "size", 1 << 20)),
  m_pawn_size(find_with_default(node, "pawn_size", 1 << 20))
{}

Config::Tablebases::Tablebases(const YAML::Node& node):
  m_cache_size(find_with_default(node, "size", 1 << 20))
{}

Config::MoveOrdering::MoveOrdering(const YAML::Node& node):
  m_use_hash_move(find_with_default(node, "use_hash_move", true)),
  m_use_see(find_with_default(node, "use_see", true)),
  m_use_killers(find_with_default(node, "use_killers", true))
{}

} // namespace olaf
