#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <yaml-cpp/yaml.h>

namespace olaf
{

class Config
{
public:
  explicit Config(const std::string& config);

  Config();

  class Evaluation {
  };

  class Search {
  public:
    explicit Search(const YAML::Node& node);

    int default_moves_to_play() const { return m_default_moves_to_play; }

    int min_depth() const { return m_min_depth; }

    int sequential_depth() const { return m_sequential_depth; }

    bool use_quiescent_search() const { return m_use_quiescent_search; }

    int initial_window() const { return m_initial_window; }

  private:
    const int m_default_moves_to_play;

    const int m_min_depth;

    const int m_sequential_depth;

    const bool m_use_quiescent_search;

    const int m_initial_window;
  };

  class TranspositionTable {
  public:
    explicit TranspositionTable(const YAML::Node& node);

    long size() const { return m_size; }

  private:
    const int m_size;
  };

  class Tablebases {
  public:
    explicit Tablebases(const YAML::Node& node);

    int cache_size() const { return m_cache_size; }

  private:
    const int m_cache_size;
  };

  class MoveOrdering {
  public:
    explicit MoveOrdering(const YAML::Node& node);

    bool use_hash_move() const { return m_use_hash_move; }

    bool use_see() const { return m_use_see; }

    bool use_killers() const { return m_use_killers; }

  private:
    const bool m_use_hash_move;

    const bool m_use_see;

    const bool m_use_killers;
  };

  const Evaluation& evaluation() const { return m_evaluation; }

  const Search& search() const { return m_search; }

  const TranspositionTable& transposition_table() const { return m_transposition_table; }

  const Tablebases& tablebases() const { return m_tablebases; }

  const MoveOrdering& move_ordering() const { return m_move_ordering; }

private:
  const YAML::Node m_config;

  const Evaluation m_evaluation;

  const Search m_search;

  const TranspositionTable m_transposition_table;

  const Tablebases m_tablebases;

  const MoveOrdering m_move_ordering;
};

} // namespace olaf

#endif // CONFIG_H
