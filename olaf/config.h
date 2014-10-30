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

  class ConfigSection {
  public:
    explicit ConfigSection(const YAML::Node& node);
  protected:
    const YAML::Node m_node;
  };

  class Evaluation : public ConfigSection {
  public:
    using ConfigSection::ConfigSection;
  };

  class Search : public ConfigSection {
  public:
    using ConfigSection::ConfigSection;

    long time_millis() const;

    int min_depth() const;

    int sequential_depth() const;
  };

  class TranspositionTable : public ConfigSection {
  public:
    using ConfigSection::ConfigSection;

    long size() const;
  };

  class MoveOrdering : public ConfigSection {
  public:
    using ConfigSection::ConfigSection;

    bool use_hash_move() const;

    bool use_see() const;

    bool use_killers() const;
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
