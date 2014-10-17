#include "sanparser.h"

#include <algorithm>
#include <string>
#include <memory>

#include "piece.h"
#include "pieceset.h"
#include "move.h"

using namespace std;

static const string c_castle_k = "O-O";
static const string c_castle_q = "O-O-O";
static const string c_capture_symbols = ":x";
static const char c_promotion_symbol = '=';

SanParser::SanParser(unique_ptr<MoveGenerator> generator,
                     unique_ptr<MoveCreator> creator):
  m_generator(move(generator)),
  m_creator(move(creator))
{}

bool SanParser::parse(const string& san_move,
                      const ChessBoard& board,
                      Move* const move) const
{
#define CHECK_NOT_END(it, end) if (it == end) { return false; }
  const bool is_castle_k = san_move.find(c_castle_k) == 0;
  const bool is_castle_q = san_move.find(c_castle_q) == 0;
  if (is_castle_k || is_castle_q) {
    Position::column_t destination_column = is_castle_q
        ? Position::c_queens_bishop_column
        : Position::c_kings_knight_column;
    Position source(ground_line(board.turn_color()), Position::c_king_column);
    Position destination(ground_line(board.turn_color()), destination_column);
    if (!m_creator->valid_move(board, source, destination)) {
      return false;
    }
    *move = m_creator->create_move(board, source, destination);
    return true;
  }
  const string::const_iterator begin = san_move.begin();
  string::const_iterator it = begin;
  const string::const_iterator end = san_move.end();
  CHECK_NOT_END(it, end);
  const char symbol = *it;
  Piece::piece_index_t piece_index = PieceSet::instance().pawn().piece_index();
  for (const Piece* const piece : PieceSet::instance().pieces()) {
    if (piece->symbol(Color::White) == symbol) {
      piece_index = piece->piece_index();
    }
  }
  if (piece_index != PieceSet::instance().pawn().piece_index()) {
    ++it;
  }
  CHECK_NOT_END(it, end);
  Position source;
  bool source_row_valid = false;
  bool source_column_valid = false;
  bool capture = false;
  if (Position::rows.find(*it) != string::npos) {
    source = Position(Position::rows.find(*it), -1);
    source_row_valid = true;
    ++it;
  } else if (Position::columns.find(*it) != string::npos) {
    const string::const_iterator next = it + 1;
    CHECK_NOT_END(next, end);
    if (Position::columns.find(*next) != string::npos
        || c_capture_symbols.find(*next) != string::npos) {
      // The found row is certainly the column disambiguation
      source = Position(-1, Position::columns.find(*it));
      source_column_valid = true;
      ++it;
    } else if (Position::rows.find(*next) != string::npos) {
      // In this case, we have to go even one step further to
      // decide whether this is the source or the target square.
      const string::const_iterator next_next = next + 1;
      if (next_next != end
          && (Position::columns.find(*next_next) != string::npos
              || c_capture_symbols.find(*next_next) != string::npos)) {
        // Yep, it was a disambiguation, so it is the source.
        source = Position(Position::rows.find(*next),
                          Position::columns.find(*it));
        source_row_valid = true;
        source_column_valid = true;
        it += 2;
      }
    }
  }
  CHECK_NOT_END(it, end);
  if (c_capture_symbols.find(*it) != string::npos) {
    ++it;
    capture = true;
  }
  const string::const_iterator column_it = it;
  const string::const_iterator row_it = it + 1;
  CHECK_NOT_END(row_it, end);
  CHECK_NOT_END(column_it, end);
  if (Position::rows.find(*row_it) == string::npos
      || Position::columns.find(*column_it) == string::npos) {
    return false;
  }
  const Position destination(Position::rows.find(*row_it),
                             Position::columns.find(*column_it));
  bool conversion = false;
  Piece::piece_index_t conversion_piece_index = Piece::c_no_piece;
  it += 2;
  if (it != end && *it == c_promotion_symbol) {
    ++it;
    CHECK_NOT_END(it, end);
    const char symbol = *it;
    for (const Piece* const piece : PieceSet::instance().pieces()) {
      if (piece->symbol(Color::White) == symbol) {
        conversion_piece_index = piece->piece_index();
      }
    }
    if (conversion_piece_index == Piece::c_no_piece) {
      return false;
    }
    conversion = true;
  }
  vector<Move> moves = m_generator->generate_valid_moves(board);
  const Move* found_move = nullptr;
  for (const Move& mov : moves) {
    if (!(mov.destination() == destination)
        || mov.is_capture() != capture
        || mov.is_conversion() != conversion) {
      continue;
    }
    if (board.turn_board().piece_index(mov.source()) != piece_index) {
      continue;
    }
    if (conversion && mov.created_piece() != conversion_piece_index) {
      continue;
    }
    if (source_row_valid && mov.source().row() != source.row()) {
      continue;
    }
    if (source_column_valid && mov.source().column() != source.column()) {
      continue;
    }
    if (found_move != nullptr) {
      // Ambiguity!
      return false;
    }
    found_move = &mov;
  }
  if (found_move == nullptr) {
    // No valid move found!
    return false;
  }
  *move = *found_move;
  return true;
#undef CHECK_END
}
