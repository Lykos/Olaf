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

  class Evaluation {
  };

  class Search {
  public:
    explicit Search(const YAML::Node& node);

    long time_millis() const { return m_time_millis; }

    int min_depth() const { return m_min_depth; }

    int sequential_depth() const { return m_sequential_depth; }

  private:
    const int m_time_millis;

    const int m_min_depth;

    const int m_sequential_depth;
  };

  class TranspositionTable {
  public:
    explicit TranspositionTable(const YAML::Node& node);

    long size() const { return m_size; }

  private:
    const int m_size;
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

  const MoveOrdering& move_ordering() const { return m_move_ordering; }

private:
  const YAML::Node m_config;

  const Evaluation m_evaluation;

  const Search m_search;

  const TranspositionTable m_transposition_table;

  const MoveOrdering m_move_ordering;
};

} // namespace olaf

#endif // CONFIG_H
