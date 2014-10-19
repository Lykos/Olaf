#include "fenparser.h"

#include <cctype>
#include <string>
#include <sstream>

#include "chessboard.h"
#include "pieceset.h"

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

#define CONSUME(c, it, end) if (it == end || *it != c) { return false; }; ++it
#define CHECK_NOT_END(it, end) if (it == end) { return false; }

bool parse_leading_int(const string::const_iterator& end,
                       string::const_iterator* const it,
                       int* const number)
{
  CHECK_NOT_END(*it, end);
  if (!is_digit(**it)) {
    return false;
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
  return true;
}

bool parse_move_numbers(const string::const_iterator& end,
                        string::const_iterator* const it,
                        ChessBoard* const new_board) {
  CONSUME(c_space, *it, end);
  CHECK_NOT_END(*it, end);
  if (!parse_leading_int(end, it, nullptr)) {
    return false;
  }
  CONSUME(c_space, *it, end);
  int turn_number;
  if (!parse_leading_int(end, it, &turn_number)) {
    return false;
  }
  new_board->turn_number(turn_number);
  return true;
}

// static
bool FenParser::parse(const string& fen, ChessBoard* const board, int* end_position)
{
  ChessBoard new_board = create_empty_board();
  const string::const_iterator begin = fen.begin();
  string::const_iterator it = begin;
  const string::const_iterator end = fen.end();
  const PieceSet& piece_set = PieceSet::instance();
  for (Position::row_t row = Position::c_row_size - 1; row >= 0; --row) {
    int column = 0;
    while (column < Position::c_column_size) {
      CHECK_NOT_END(it, end);
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
          return false;
        }
      }
      ++it;
    }
    if (column > Position::c_column_size) {
      return false;
    }
    if (row > 0) {
      CONSUME(c_row_separator, it, end);
    }
  }
  CONSUME(c_space, it, end);
  CHECK_NOT_END(it, end);
  if (*it == c_black) {
    new_board.turn_color(Color::Black);
  } else if (*it != c_white) {
    return false;
  }
  ++it;
  CONSUME(c_space, it, end);
  while (true) {
    CHECK_NOT_END(it, end);
    const char c = *it;
    if (c == c_white_castle_k) {
      new_board.color_board(Color::White).can_castle_k(true);
    } else if (c == c_white_castle_q) {
      new_board.color_board(Color::White).can_castle_q(true);
    } else if (c == c_black_castle_k) {
      new_board.color_board(Color::Black).can_castle_k(true);
    } else if (c == c_black_castle_q) {
      new_board.color_board(Color::Black).can_castle_q(true);
    } else {
      if (c == c_dash) {
        ++it;
      }
      break;
    }
    ++it;
  }
  CONSUME(c_space, it, end);
  CHECK_NOT_END(it, end);
  if (*it >= c_a && *it <= c_h) {
    const int column = *it - c_a;
    ++it;
    CHECK_NOT_END(it, end);
    int ep_row;
    int victim_row;
    if (*it == c_three) {
      ep_row = 2;
      victim_row = 3;
    } else if (*it == c_six) {
      ep_row = 5;
      victim_row = 4;
    } else {
      return false;
    }
    Position ep_position(ep_row, column);
    Position victim_position(victim_row, column);
    new_board.ep_capture_position(ep_position);
    new_board.ep_victim_position(victim_position);
    new_board.ep_possible(true);
  } else if (*it != c_dash) {
    return false;
  }
  ++it;
  parse_move_numbers(end, &it, &new_board);
  // We don't check for validity here. A lot of FENs have invalid or no move numbers.
  *board = new_board;
  if (end_position) {
    *end_position = it - begin;
  }
  return true;
}

// static
string FenParser::serialize(const ChessBoard& board)
{
  ostringstream result;
  for (Position::row_t row = Position::c_row_size - 1; row >= 0; --row) {
    int free_columns = 0;
    for (Position::column_t column = 0; column < Position::c_column_size; ++column) {
      const Position pos(row, column);
      if (board.occupied(pos)) {
        if (free_columns > 0) {
          result << free_columns;
          free_columns = 0;
        }
        if (board.friendd(pos)) {
         result << board.turn_board().piece(pos).symbol(board.turn_color());
       } else if (board.opponent(pos)) {
         result << board.noturn_board().piece(pos).symbol(previous(board.turn_color()));
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
    result << board.ep_capture_position();
  } else {
    result << c_dash;
  }
  result << c_space;
  // TODO Handle 50 moves rule.
  result << 0;
  result << c_space;
  result << board.turn_number();
  return result.str();
}

#undef CONSUME

} // namespace olaf
#undef CHECK_NOT_END
