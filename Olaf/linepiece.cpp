#include "linepiece.h"

using namespace std;

LinePiece::LinePiece(const vector<PositionDelta>& directions);

vector<Move> LinePiece::moves(Position, Color) const;
