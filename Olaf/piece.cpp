#include "piece.h"

static const std::vector<PositionDelta> c_all_directions = {
  PositionDelta(0, -1),
  PositionDelta(0, 1),
  PositionDelta(-1, 0),
  PositionDelta(1, 0),
  PositionDelta(-1, -1),
  PositionDelta(-1, 1),
  PositionDelta(1, -1),
  PositionDelta(1, 1)
};

static const std::vector<PositionDelta> c_straight_directions = {
  PositionDelta(0, -1),
  PositionDelta(0, 1),
  PositionDelta(-1, 0),
  PositionDelta(1, 0),
};

static const std::vector<PositionDelt> c_diagonal_directions = {
  PositionDelta(-1, -1),
  PositionDelta(-1, 1),
  PositionDelta(1, -1),
  PositionDelta(1, 1)
};

static const std::vector<PositionDelta>& Piece::all_directions()
{
  return c_all_directions;
}

static const std::vector<PositionDelta>& Piece::straight_directions()
{
  return c_straight_directions;
}

static const std::vector<PositionDelta>& Piece::diagonal_directions()
{
  return c_diagonal_directions;
}
