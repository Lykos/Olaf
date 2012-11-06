#include "pawn.h"
#include "move.h"
#include "epenablaction.h"
#include "pieceset.h"

using namespace std;

Pawn::Pawn(piece_index_t piece_index, const BitBoard& initial_board, const std::vector<piece_index_t> &conversions):
  Piece(piece_index, initial_board),
  m_conversions (conversions)
{}

static const array<PositionDelta, 2> sidewards_directions = {{
  PositionDelta(0, 1),
  PositionDelta(0, -1)
}};

std::vector<Move> Pawn::moves(const Position &source,
                              const ChessBoard& board) const
{
  vector<Move> result;
  Color color = board.turn_color();
  Position simple_move_destination = source + forward_direction(color);
  // Check if square is free
  if (!board.occupied(simple_move_destination)) {
    Move simple_move (board, piece_index(), source, simple_move_destination);
    // Handle conversion, if necessary.
    if (source.row() == conversion_row(color)) {
      add_conversion_moves(result, simple_move, simple_move_destination);
    } else {
      result.push_back(simple_move);
      // Check if the pawn is at its initial position
      if (source.row() == pawn_row(color)) {
        Position double_move_destination = simple_move_destination + forward_direction(color);
        // Check if double move field is free.
        if (!board.occupied(double_move_destination)) {
          result.push_back(Move(board, piece_index(), source, double_move_destination, simple_move_destination));
        }
      }
    }
  }
  for (const PositionDelta &sidewards : sidewards_directions) {
    if (!source.in_bounds(sidewards)) {
      continue;
    }
    Position capture_destination = source + forward_direction(color) + sidewards;
    Move capture (board, piece_index(), source, capture_destination);
    // Check if capture is possible
    if (board.opponent(capture_destination)) {
      if (capture_destination.row() == conversion_row(color)) {
        add_conversion_moves(result, capture, capture_destination);
      } else {
        result.push_back(capture);
      }
    // or ep capture is possible
    } else if (board.ep_possible() && capture_destination == board.ep_capture_position()) {
      capture.capture_ep(board);
      result.push_back(capture);
    }
  }
  return result;
}

bool Pawn::can_move(const Position &source, const Position &destination, const ChessBoard &board) const
{
  if (destination.row() == conversion_row(board.turn_color())) {
    return false;
  }
  Position step = source + forward_direction(board.turn_color());
  if (destination.row() == step.row() && abs(destination.column() - step.column()) == 1 && board.opponent(destination)) {
    return true;
  }
  if (board.occupied(step)) {
    return false;
  }
  if (destination == step) {
    return true;
  }
  if (source.row() != pawn_row(board.turn_color())) {
    return false;
  }
  Position two_step = step + forward_direction(board.turn_color());
  return destination == two_step && !board.occupied(step) && !board.occupied(two_step);
}

bool Pawn::can_move(const Position &source, const Position &destination, const ChessBoard &board, piece_index_t conversion) const
{
  if (destination.row() != conversion_row(board.turn_color())) {
    return false;
  }
  Position step = source + forward_direction(board.turn_color());
  bool conversion_valid = false;
  for (piece_index_t conv : m_conversions) {
    if (conversion == conv) {
      conversion_valid = true;
      break;
    }
  }
  if (!conversion_valid) {
    return false;
  }
  if (destination.row() == step.row() && abs(destination.column() - step.column()) == 1 && board.opponent(destination)) {
    return true;
  }
  return destination == step && !board.occupied(step);
}

Move Pawn::move(const Position &source, const Position &destination, const ChessBoard &board) const
{
  Position step = source + forward_direction(board.turn_color());
  Position two_step = step + forward_direction(board.turn_color());
  if (destination == two_step) {
    return Move(board, piece_index(), source, destination, step);
  } else {
    return Move(board, piece_index(), source, destination);
  }
}

Move Pawn::move(const Position &source, const Position &destination, const ChessBoard &board, piece_index_t conversion) const
{
  Move result (board, piece_index(), source, destination);
  result.conversion(destination, piece_index(), conversion);
  return result;
}

void Pawn::add_conversion_moves(vector<Move>& moves, const Move& base_move, const Position& position) const
{
  for (piece_index_t piece_index : m_conversions) {
    Move conversion (base_move);
    conversion.conversion(position, this->piece_index(), piece_index);
    moves.push_back(conversion);
  }
}
