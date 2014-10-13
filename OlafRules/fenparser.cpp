#include "fenparser.h"

#include <cctype>
#include <string>

#include "chessboard.h"
#include "pieceset.h"

using namespace std;

static const char c_row_separator = '/';
static const char c_zero = '0';
static const char c_one = '1';
static const char c_three = '3';
static const char c_six = '6';
static const char c_eight = '8';
static const char c_nine = '8';
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
  CHECK_NOT_END(*it, end);
  while (is_digit(**it)) {
    if (number) {
      *number = *number * 10 + to_digit(**it);
    }
    ++*it;
  }
  return true;
}

// static
bool FenParser::parse(const string& fen, ChessBoard* const board)
{
  ChessBoard new_board = create_empty_board();
  string::const_iterator it = fen.begin();
  string::const_iterator end = fen.end();
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
    if (row < Position::c_row_size - 1) {
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
    board->ep_capture_position(ep_position);
    board->ep_victim_position(victim_position);
    board->ep_possible(true);
  } else if (*it != c_dash) {
    return false;
  }
  ++it;
  CONSUME(c_space, it, end);
  if (!parse_leading_int(end, &it, nullptr)) {
    return false;
  }
  CONSUME(c_space, it, end);
  int turn_number;
  if (!parse_leading_int(end, &it, &turn_number)) {
    return false;
  }
  new_board.turn_number(turn_number);
  if (it != end) {
    return false;
  }
  *board = new_board;
  return true;
}

#undef CONSUME
#undef CHECK_NOT_END
