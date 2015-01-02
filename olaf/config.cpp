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

Config::Config(const std::string& config_string):
  config(YAML::Load(config_string)),
  evaluation(),
  search(config["search"]),
  transposition_table(config["transposition_table"]),
  tablebases(config["tablebases"]),
  move_ordering(config["move_ordering"])
{}

Config::Config():
  Config("")
{}

Config::Search::Search(const YAML::Node& node):
  default_moves_to_play(find_with_default(node, "default_moves_to_play", 40)),
  min_depth(find_with_default(node, "min_depth", 1)),
  sequential_depth(find_with_default(node, "sequential_depth", 2)),
  use_quiescent_search(find_with_default(node, "use_quiescent_search", true)),
  initial_window(find_with_default(node, "initial_window", 25))
{}

Config::TranspositionTable::TranspositionTable(const YAML::Node& node):
  size(find_with_default(node, "size", 1 << 20)),
  pawn_size(find_with_default(node, "pawn_size", 1 << 20))
{}

Config::Tablebases::Tablebases(const YAML::Node& node):
  enabled(find_with_default(node, "enabled", false)),
  cache_size(find_with_default(node, "size", 1 << 20))
{}

Config::MoveOrdering::MoveOrdering(const YAML::Node& node):
  use_hash_move(find_with_default(node, "use_hash_move", true)),
  use_promotions(find_with_default(node, "use_promotions", true)),
  use_see(find_with_default(node, "use_see", true)),
  use_killers(find_with_default(node, "use_killers", true))
{}

} // namespace olaf
