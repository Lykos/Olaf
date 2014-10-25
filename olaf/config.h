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

    long search_time_millis() const;

    int min_search_depth() const;

    int sequential_search_depth() const;
  };

  class TranspositionTable : public ConfigSection {
  public:
    using ConfigSection::ConfigSection;

    long size() const;
  };

  const Evaluation& evaluation() const { return m_evaluation; }

  const Search& search() const { return m_search; }

  const TranspositionTable& transposition_table() const { return m_transposition_table; }

private:
  const YAML::Node m_config;

  const Evaluation m_evaluation;

  const Search m_search;

  const TranspositionTable m_transposition_table;
};

} // namespace olaf

#endif // CONFIG_H
