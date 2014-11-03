#include "olaf/parse/fenparser.h"

#include <cctype>
#include <string>
#include <sstream>

#include "olaf/rules/chessboard.h"
#include "olaf/rules/pieceset.h"

using namespace std;

namespace olaf
{

static const char c_row_separator = '/';
static const char c_zero = '0';
static const char c_one = '1';
static const char c_three = '3';
static const char c_six = '6';
static const char c_eight = '8';
static const char c_nine = '9';
static const char c_a = 'a';
static const char c_h = 'h';
static const char c_space = ' ';
static const char c_white = 'w';
static const char c_black = 'b';
static const char c_white_castle_k = 'K';
static const char c_white_castle_q = 'Q';
static const char c_black_castle_k = 'k';
static const char c_black_castle_q = 'q';
static const char c_dash = '-';

bool is_digit(const char c)
{
  return c_zero <= c && c <= c_nine;
}

int to_digit(const char c)
{
  return c - c_zero;
}

#define SYNTAX_ERROR "FEN syntax error: "
#define CONSUME(c, it, end) \
  if (it == end) { ostringstream oss; oss << SYNTAX_ERROR << "Expected " << c << " got end"; return Status::error(oss.str()); }; \
  if (*it != c) { ostringstream oss; oss << SYNTAX_ERROR << "Expected " << c << " got " << *it; return Status::error(oss.str()); }; \
  ++it
#define CHECK_NOT_END(it, end, message) if (it == end) { return Status::error(SYNTAX_ERROR message); }
#define FORWARD_BAD(expr) \
  { \
    const Status& status = expr; \
    if (!status.ok()) { return status; } \
  }

Status parse_leading_int(const string::const_iterator& end,
                         string::const_iterator* const it,
                         int* const number)
{
  CHECK_NOT_END(*it, end, "Expected number, got end of string");
  if (!is_digit(**it)) {
    ostringstream oss;
    oss << SYNTAX_ERROR << "Expected digit, got " << **it;
    return Status::error(oss.str());
  }
  if (number) {
    *number = to_digit(**it);
  }
  ++*it;
  while (*it != end && is_digit(**it)) {
    if (number) {
      *number = *number * 10 + to_digit(**it);
    }
    ++*it;
  }
  return Status::valid();
}

Status parse_move_numbers(const string::const_iterator& end,
                          string::const_iterator* const it,
                          ChessBoard* const new_board) {
  CONSUME(c_space, *it, end);
  CHECK_NOT_END(*it, end, "Expected move numbers, got end of string");
  int reversible_plies;
  FORWARD_BAD(parse_leading_int(end, it, &reversible_plies));
  new_board->reversible_plies(reversible_plies);
  CONSUME(c_space, *it, end);
  int turn_number;
  FORWARD_BAD(parse_leading_int(end, it, &turn_number));
  new_board->turn_number(turn_number);
  return Status::valid();
}

// static
Status FenParser::parse(const string& fen, ChessBoard* const board, int* end_position)
{
  ChessBoard new_board = create_empty_board();
  const string::const_iterator begin = fen.begin();
  string::const_iterator it = begin;
  const string::const_iterator end = fen.end();
  const PieceSet& piece_set = PieceSet::instance();
  for (Position::index_t row = Position::c_row_size - 1; row >= 0; --row) {
    int column = 0;
    while (column < Position::c_column_size) {
      CHECK_NOT_END(it, end, "");
      const char c = *it;
      if (c >= c_one && c <= c_eight) {
        column += c - c_zero;
      } else {
        bool found = false;
        for (const Piece* const piece : piece_set.pieces()) {
          Color color;
          if (piece->symbol(Color::White) == c) {
            color = Color::White;
          } else if (piece->symbol(Color::Black) == c) {
            color = Color::Black;
          } else {
            continue;
          }
          Position position(row, column);
          new_board.add_piece(color, piece->piece_index(), position);
          found = true;
          ++column;
          break;
        }
        if (!found) {
          ostringstream oss;
          oss << SYNTAX_ERROR << "Invalid symbol " << *it << " on the FEN board. Only 1-8 and rnbqkpRNBQkP are allowed.";
          return Status::error(oss.str());
        }
      }
      ++it;
    }
    if (column > Position::c_column_size) {
      ostringstream oss;
      oss << SYNTAX_ERROR << "Row " << Position::c_row_size - row << " has more than 8 columns.";
      return Status::error(oss.str());
    }
    if (row > 0) {
      CONSUME(c_row_separator, it, end);
    }
  }
  CONSUME(c_space, it, end);
  CHECK_NOT_END(it, end, "Expected turn color, got end");
  if (*it == c_black) {
    new_board.turn_color(Color::Black);
  } else if (*it != c_white) {
    ostringstream oss;
    oss << SYNTAX_ERROR << *it << " is not a valid color. Only w and b are possible.";
    return Status::error(oss.str());
  }
  ++it;
  CONSUME(c_space, it, end);
  while (true) {
    CHECK_NOT_END(it, end, "");
    const char c = *it;
    if (c == c_white_castle_k) {
      new_board.can_castle_k(Color::White, true);
    } else if (c == c_white_castle_q) {
      new_board.can_castle_q(Color::White, true);
    } else if (c == c_black_castle_k) {
      new_board.can_castle_k(Color::Black, true);
    } else if (c == c_black_castle_q) {
      new_board.can_castle_q(Color::Black, true);
    } else {
      if (c == c_dash) {
        ++it;
      }
      break;
    }
    ++it;
  }
  CONSUME(c_space, it, end);
  CHECK_NOT_END(it, end, "Expected en passent position, got end");
  if (*it >= c_a && *it <= c_h) {
    const int column = *it - c_a;
    ++it;
    CHECK_NOT_END(it, end, "");
    int row;
    if (*it == c_three) {
      row = 2;
    } else if (*it == c_six) {
      row = 5;
    } else {
      ostringstream oss;
      oss << SYNTAX_ERROR << *it << " is not a valid en passent row. Only 3 and 6 are possible.";
      return Status::error(oss.str());
    }
    const Position ep_position(row, column);
    new_board.ep_captures(BitBoard(ep_position));
  } else if (*it != c_dash) {
    ostringstream oss;
    oss << SYNTAX_ERROR << "Expected en passent position or dash, got " << *it;
    return Status::error(oss.str());
  }
  ++it;
  parse_move_numbers(end, &it, &new_board);
  // We don't check for validity here. A lot of FENs have invalid or no move numbers.
  *board = new_board;
  if (end_position) {
    *end_position = it - begin;
  }
  return Status::valid();
}

#undef CONSUME
#undef CHECK_NOT_END
#undef FORWARD_BAD
#undef SYNTAX_ERROR

// static
string FenParser::serialize(const ChessBoard& board)
{
  ostringstream result;
  for (Position::index_t row = Position::c_row_size - 1; row >= 0; --row) {
    int free_columns = 0;
    for (Position::index_t column = 0; column < Position::c_column_size; ++column) {
      const Position pos(row, column);
      if (board.occupied(pos)) {
        if (free_columns > 0) {
          result << free_columns;
          free_columns = 0;
        }
        if (board.friendd(pos)) {
         result << board.piece(pos).symbol(board.turn_color());
       } else if (board.opponent(pos)) {
         result << board.piece(pos).symbol(other_color(board.turn_color()));
       }
      } else {
        ++free_columns;
      }
    }
    if (free_columns > 0) {
      result << free_columns;
    }
    if (row > 0) {
      result << c_row_separator;
    }
  }
  result << c_space;
  result << (board.turn_color() == Color::White ? c_white : c_black);
  result << c_space;
  bool castle = false;
  if (board.color_board(Color::White).can_castle_k()) {
    result << c_white_castle_k;
    castle = true;
  }
  if (board.color_board(Color::White).can_castle_q()) {
    result << c_white_castle_q;
    castle = true;
  }
  if (board.color_board(Color::Black).can_castle_k()) {
    result << c_black_castle_k;
    castle = true;
  }
  if (board.color_board(Color::Black).can_castle_q()) {
    result << c_black_castle_q;
    castle = true;
  }
  if (!castle) {
    result << c_dash;
  }
  result << c_space;
  if (board.ep_possible()) {
    result << board.ep_captures().first_position();
  } else {
    result << c_dash;
  }
  result << c_space;
  result << board.reversible_plies();
  result << c_space;
  result << board.turn_number();
  return result.str();
}

} // namespace olaf
