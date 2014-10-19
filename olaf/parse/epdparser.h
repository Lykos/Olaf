#ifndef EPDPARSER_H
#define EPDPARSER_H

#include <memory>
#include <string>

#include "olaf/parse/sanparser.h"

namespace olaf
{

class EpdPosition;

class EpdParser
{
public:
  explicit EpdParser(std::unique_ptr<SanParser> san_parser);

  bool parse(const std::string& epd, EpdPosition* position) const;

private:
  void parse_id(const std::string& id, EpdPosition* position) const;

  void parse_am(const std::string& am, EpdPosition* position) const;

  void parse_bm(const std::string& bm, EpdPosition* position) const;

  std::unique_ptr<SanParser> m_san_parser;
};

} // namespace olaf

#endif // EPDPARSER_H