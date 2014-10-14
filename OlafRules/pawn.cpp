#include "pawn.h"

#include "move.h"
#include "epenableaction.h"
#include "pieceset.h"
#include "movebuilder.h"

using namespace std;

Pawn::Pawn(const piece_index_t piece_index,
           const char symbol,
           const BitBoard& initial_board,
           const std::vector<piece_index_t>& conversions):
  Piece(piece_index, symbol, initial_board),
  m_conversions (conversions)
{}

static const array<PositionDelta, 2> sidewards_directions = {{
  PositionDelta(0, 1),
  PositionDelta(0, -1)
}};

std::vector<Move> Pawn::moves(const Position& source,
                              const ChessBoard& board) const
{
  vector<Move> result;
  const Color color = board.turn_color();
  const Position& simple_move_destination =
      source + forward_direction(color);
  // Check if square is free
  if (!board.occupied(simple_move_destination)) {
    // Handle conversion, if necessary.
    if (source.row() == conversion_row(color)) {
      add_conversion_moves(&result, board, source, simple_move_destination);
    } else {
      result.emplace_back(move(source, simple_move_destination, board));
      const Position& double_move_destination =
          simple_move_destination + forward_direction(color);
      if (!board.occupied(double_move_destination)) {
        result.emplace_back(move(source, double_move_destination, board));
      }
    }
  }
  for (const PositionDelta& sidewards : sidewards_directions) {
    if (!source.in_bounds(sidewards)) {
      continue;
    }
    Position capture_destination = source + forward_direction(color) + sidewards;
    // Check if capture is possible
    if (board.opponent(capture_destination)
        || (board.ep_possible()
            && capture_destination == board.ep_capture_position())) {
      if (capture_destination.row() == conversion_row(color)) {
        add_conversion_moves(&result, board, source, capture_destination);
      } else {
        result.emplace_back(move(source, capture_destination, board));
      }
    }
  }
  return result;
}

bool Pawn::can_move(const Position& source,
                    const Position& destination,
                    const ChessBoard& board) const
{
  if (!internal_can_move(source, destination, board)) {
    return false;
  }
  return destination.row() != conversion_row(board.turn_color());
}

bool Pawn::can_move(const Position& source,
                    const Position& destination,
                    const ChessBoard& board,
                    const piece_index_t conversion) const
{
  if (!internal_can_move(source, destination, board)) {
    return false;
  }
  if (destination.row() != conversion_row(board.turn_color())) {
    return false;
  }
  for (piece_index_t conv : m_conversions) {
    if (conversion == conv) {
      return true;
    }
  }
  return false;
}

Move Pawn::move(const Position& source,
                const Position& destination,
                const ChessBoard& board) const
{
  const Position& step = source + forward_direction(board.turn_color());
  const Position& two_step = step + forward_direction(board.turn_color());
  MoveBuilder builder(board, source, destination);
  if (destination == two_step) {
    builder.enable_ep(step);
  }
  return builder.build();
}

Move Pawn::move(const Position& source,
                const Position& destination,
                const ChessBoard& board,
                const piece_index_t conversion) const
{
  MoveBuilder builder(board, source, destination);
  builder.conversion(destination, piece_index(), conversion);
  return builder.build();
}

void Pawn::add_conversion_moves(vector<Move>* const moves,
                                const ChessBoard& board,
                                const Position& source,
                                const Position& destination) const
{
  for (piece_index_t piece_index : m_conversions) {
    moves->emplace_back(move(source, destination, board, piece_index));
  }
}

bool Pawn::internal_can_move(const Position& source,
                             const Position& destination,
                             const ChessBoard& board) const
{
  if (!Piece::can_move(source, destination, board)) {
    return false;
  }
  const PositionDelta& delta = forward_direction(board.turn_color());
  const Position& step = source + delta;
  // Handle capture.
  if (destination.row() == step.row()
      && abs(destination.column() - step.column()) == 1) {
    return board.opponent(destination)
        || (board.ep_possible()
            && destination == board.ep_capture_position());
  }
  if (destination.column() != step.column()) {
    return false;
  }
  // blocked pawn
  if (board.occupied(step)) {
    return false;
  }
  // valid single step
  if (destination == step) {
    return true;
  }
  // double step
  if (source.row() != pawn_row(board.turn_color())) {
    return false;
  }
  if (board.occupied(destination)) {
    return false;
  }
  const Position& two_step = step + delta;
  return destination == two_step;
}
