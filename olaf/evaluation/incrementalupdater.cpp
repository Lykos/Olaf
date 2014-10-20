#include "olaf/evaluation/incrementalupdater.h"

#include <vector>
#include <iostream>

#include "olaf/rules/pieceset.h"

using namespace std;

namespace olaf
{

static array<int, 6> generate_piece_values()
{
  const PieceSet& set = PieceSet::instance();
  array<int, 6> piece_values;
  piece_values[set.rook().piece_index()] = 500;
  piece_values[set.knight().piece_index()] = 320;
  piece_values[set.bishop().piece_index()] = 330;
  piece_values[set.queen().piece_index()] = 900;
  piece_values[set.king().piece_index()] = 25000;
  piece_values[set.pawn().piece_index()] = 100;
  return piece_values;
}

static const array<int, 64> c_piece_square_values_rook = {
  0,  0,  0,  5,  5,  0,  0,  0,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  -5,  0,  0,  0,  0,  0,  0, -5,
  5, 10, 10, 10, 10, 10, 10,  5,
  0,  0,  0,  0,  0,  0,  0,  0
};

static const array<int, 64> c_piece_square_values_knight = {
  -50,-40,-30,-30,-30,-30,-40,-50,
  -40,-20,  0,  5,  5,  0,-20,-40,
  -30,  5, 10, 15, 15, 10,  5,-30,
  -30,  0, 15, 20, 20, 15,  0,-30,
  -30,  5, 15, 20, 20, 15,  5,-30,
  -30,  0, 10, 15, 15, 10,  0,-30,
  -40,-20,  0,  0,  0,  0,-20,-40,
  -50,-40,-30,-30,-30,-30,-40,-50,
};

static const array<int, 64> c_piece_square_values_bishop = {
  -20,-10,-10,-10,-10,-10,-10,-20,
  -10,  5,  0,  0,  0,  0,  5,-10,
  -10, 10, 10, 10, 10, 10, 10,-10,
  -10,  0, 10, 10, 10, 10,  0,-10,
  -10,  5,  5, 10, 10,  5,  5,-10,
  -10,  0,  5, 10, 10,  5,  0,-10,
  -10,  0,  0,  0,  0,  0,  0,-10,
  -20,-10,-10,-10,-10,-10,-10,-20,
};

static const array<int, 64> c_piece_square_values_queen = {
  -20,-10,-10, -5, -5,-10,-10,-20,
  -10,  0,  5,  0,  0,  0,  0,-10,
  -10,  5,  5,  5,  5,  5,  0,-10,
   0,   0,  5,  5,  5,  5,  0, -5,
  -5,   0,  5,  5,  5,  5,  0, -5,
  -10,  0,  5,  5,  5,  5,  0,-10,
  -10,  0,  0,  0,  0,  0,  0,-10,
  -20,-10,-10, -5, -5,-10,-10,-20
};

static const array<int, 64> c_piece_square_values_king = {
  20, 30, 10,  0,  0, 10, 30, 20,
  20, 20,  0,  0,  0,  0, 20, 20,
  -10,-20,-20,-20,-20,-20,-20,-10,
  -20,-30,-30,-40,-40,-30,-30,-20,
  -30,-40,-40,-50,-50,-40,-40,-30,
  -30,-40,-40,-50,-50,-40,-40,-30,
  -30,-40,-40,-50,-50,-40,-40,-30,
  -30,-40,-40,-50,-50,-40,-40,-30
};

static const array<int, 64> c_piece_square_values_pawn = {
  0,  0,  0,  0,  0,  0,  0,  0,
  5, 10, 10,-20,-20, 10, 10,  5,
  5, -5,-10,  0,  0,-10, -5,  5,
  0,  0,  0, 20, 20,  0,  0,  0,
  5,  5, 10, 25, 25, 10,  5,  5,
  10, 10, 20, 30, 30, 20, 10, 10,
  50, 50, 50, 50, 50, 50, 50, 50,
  0,  0,  0,  0,  0,  0,  0,  0
};

static array<array<int, 64>, 6> generate_piece_square_values()
{
  const PieceSet& set = PieceSet::instance();
  array<array<int, 64>, 6> piece_square_values;
  piece_square_values[set.rook().piece_index()] = c_piece_square_values_rook;
  piece_square_values[set.knight().piece_index()] = c_piece_square_values_knight;
  piece_square_values[set.bishop().piece_index()] = c_piece_square_values_bishop;
  piece_square_values[set.queen().piece_index()] = c_piece_square_values_queen;
  piece_square_values[set.king().piece_index()] = c_piece_square_values_king;
  piece_square_values[set.pawn().piece_index()] = c_piece_square_values_pawn;
  return piece_square_values;
}

static int piece_value(const Color color,
                       const Piece::piece_index_t piece_index,
                       const Position& position)
{
  static const array<int, 6> piece_values = generate_piece_values();
  static const array<array<int, 64>, 6> piece_square_values = generate_piece_square_values();
  int result = piece_values[piece_index];
  int position_index;
  if (color == Color::White) {
    position_index = index(position);
  } else {
    Position pos(Position::c_row_size - 1 - position.row(), position.column());
    position_index = index(pos);
  }
  result += piece_square_values[piece_index][position_index];
  return result;
}

void IncrementalUpdater::calculate(ChessBoard* board)
{
  board->m_incremental_score_white = 0;
  for (const Color color : {Color::Black, Color::White}) {
    const ColorBoard& color_board = board->color_board(color);
    for (const PieceBoard& piece_board : color_board.piece_boards()) {
      const Piece::piece_index_t piece_index = piece_board.piece().piece_index();
      for (const Position& position : piece_board.positions()) {
        add_piece(color, piece_index, position, board);
      }
    }
  }
}

void IncrementalUpdater::remove_piece(const Color color,
                                      const Piece::piece_index_t piece_index,
                                      const Position& position,
                                      ChessBoard* const board)
{
  const int value = -piece_value(color, piece_index, position);
  board->m_incremental_score_white += color == Color::White ? value : -value;
}

void IncrementalUpdater::add_piece(const Color color,
                                   const Piece::piece_index_t piece_index,
                                   const Position& position,
                                   ChessBoard* const board)
{
  const int value = piece_value(color, piece_index, position);
  board->m_incremental_score_white += color == Color::White ? value : -value;
}

} // namespace olaf