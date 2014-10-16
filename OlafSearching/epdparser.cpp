#include "epdparser.h"

#include <cassert>

#include "epdposition.h"
#include "OlafRules/fenparser.h"
#include "sanparser.h"

using namespace std;

static const string c_id = "id";
static const string c_bm = "bm";
static const char c_space = ' ';
static const char c_quote = '"';
static const string c_semicolon = "; ";

EpdParser::EpdParser(unique_ptr<SanParser> san_parser):
  m_san_parser(move(san_parser))
{}

bool EpdParser::parse(const string& epd, EpdPosition* const position) const
{
  int fen_end_position;
  if (!FenParser::parse(epd, &(position->board), &fen_end_position)) {
    return false;
  }
  unsigned int it = fen_end_position;
  while (it < epd.size()) {
    // TODO semicolons in strings
    const unsigned long end = epd.find(c_semicolon, it);
    const unsigned long command_length = (end == string::npos ? epd.size(): end) - it;
    assert(command_length > 0);
    // If we don't find a semicolon, the command goes to the end.
    const string& command = epd.substr(it, command_length);
    if (epd.find(c_id, it) == it) {
      parse_id(command.substr(c_id.size() + 1), position);
    } else if (epd.find(c_bm, it) == it) {
      parse_bm(command.substr(c_bm.size() + 1), position);
    }
    it += command_length + c_semicolon.size();
  }
  return true;
}

void EpdParser::parse_id(const string& id, EpdPosition* const position) const
{
  string::const_iterator it = id.begin();
  const string::const_iterator end = id.end();
  if (it == end || *it != c_quote) {
    return;
  }
  ++it;
  string parsed_id;
  for (; it < end && *it != c_quote; ++it) {
    parsed_id.push_back(*it);
  }
  if (it != end) {
    position->id = parsed_id;
  }
}

void EpdParser::parse_bm(const string& bm, EpdPosition* const position) const
{
  Move move;
  if (m_san_parser->parse(bm.substr(1, string::npos), position->board, &move)) {
    position->best_moves.push_back(move);
  }
}
