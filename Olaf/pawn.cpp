#include "pawn.h"
#include "epenablaction.h"

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
                              const ChessBoard& board,
                              const BitBoard &opponents,
                              const BitBoard &friends) const
{
  vector<Move> result;
  Color color = board.turn();
  BitBoard occupied = opponents | friends;
  Position simple_move_destination = source + forward_direction(color);
  // Check if square is free
  if (!occupied.get(simple_move_destination)) {
    Move simple_move (piece_index(), source, simple_move_destination);
    simple_move.disable_ep();
    // Handle conversion, if necessary.
    if (source.row() == conversion_row(color)) {
      add_conversions(result, simple_move, simple_move_destination);
    } else {
      result.push_back(simple_move);
      // Check if the pawn is at its initial position
      if (source.row() == pawn_row(color)) {
        Position double_move_destination = simple_move_destination + forward_direction(color);
        // Check if double move field is free.
        if (!occupied.get(double_move_destination)) {
          Move double_move (piece_index(), source, double_move_destination);
          double_move.enable_ep(simple_move_destination, double_move_destination);
        }
      }
    }
  }
  for (const PositionDelta &sidewards : sidewards_directions) {
    if (!source.in_bounds(sidewards)) {
      continue;
    }
    Position capture_destination = source + forward_direction(color) + sidewards;
    Move capture (piece_index(), source, capture_destination);
    capture.disable_ep();
    // Check if capture is possible
    if (opponents.get(capture_destination)) {
      capture.capture(board.noturn_board().piece_index(capture_destination), capture_destination);
      if (capture_destination.row() == conversion_row(color)) {
        add_conversions(result, capture, capture_destination);
      } else {
        result.push_back(capture);
      }
    } else if (board.ep_possible() && capture_destination == board.ep_capture_position()) {
      capture.capture(board.noturn_board().piece_index(capture_destination), board.ep_victim_position());
      result.push_back(capture);
    }
  }
  return result;
}

void Pawn::add_conversions(vector<Move>& moves, const Move& base_move, const Position& position) const
{
  for (piece_index_t piece_index : m_conversions) {
    Move conversion (base_move);
    conversion.conversion(position, this->piece_index(), piece_index);
    moves.push_back(conversion);
  }
}
