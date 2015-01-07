#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <yaml-cpp/yaml.h>

namespace olaf
{

struct Config
{
public:
  explicit Config(const std::string& config_string);

  Config();

  class Evaluation {
  };

  struct Search {
    explicit Search(const YAML::Node& node);

    /**
     * @brief default_moves_to_play is used for time estimation if there
     *        is no upper bound on the number of moves to play given.
     */
    const int default_moves_to_play;

    const int min_depth;

    const int sequential_depth;

    const int initial_window;
  };

  struct TranspositionTable {
    explicit TranspositionTable(const YAML::Node& node);

    const int size;

    const int pawn_size;
  };

  struct Tablebases {
    explicit Tablebases(const YAML::Node& node);

    const bool enabled;

    const int cache_size;
  };

  struct MoveOrdering {
    explicit MoveOrdering(const YAML::Node& node);

    const bool use_hash_move;

    const bool use_promotions;

    const bool use_see;

    const bool use_killers;
  };

  const YAML::Node config;

  const Evaluation evaluation;

  const Search search;

  const TranspositionTable transposition_table;

  const Tablebases tablebases;

  const MoveOrdering move_ordering;
};

} // namespace olaf

#endif // CONFIG_H
