#include "pieceset.h"
#include "linepiece.h"
#include "pawn.h"
#include "oncepiece.h"
#include "bitboard.h"

using namespace std;

static const vector<PositionDelta> c_queen_directions = {
  PositionDelta(0, -1),
  PositionDelta(0, 1),
  PositionDelta(-1, 0),
  PositionDelta(1, 0),
  PositionDelta(-1, -1),
  PositionDelta(-1, 1),
  PositionDelta(1, -1),
  PositionDelta(1, 1)
};

static const vector<PositionDelta> c_rook_directions = {
  PositionDelta(0, -1),
  PositionDelta(0, 1),
  PositionDelta(-1, 0),
  PositionDelta(1, 0),
};

static const vector<PositionDelta> c_bishop_directions = {
  PositionDelta(-1, -1),
  PositionDelta(-1, 1),
  PositionDelta(1, -1),
  PositionDelta(1, 1)
};

static const vector<PositionDelta> c_knight_directions = {
  PositionDelta(-1, -2),
  PositionDelta(-2, -1),
  PositionDelta(-1, 2),
  PositionDelta(-2, 1),
  PositionDelta(1, -2),
  PositionDelta(2, -1),
  PositionDelta(1, 2),
  PositionDelta(2, 1)
};

static const BitBoard c_rook_initial_board (0x8100000000000000);

static const BitBoard c_knight_initial_board (0x4200000000000000);

static const BitBoard c_bishop_initial_board (0x2400000000000000);

static const BitBoard c_queen_initial_board (0x1000000000000000);

static const BitBoard c_king_initial_board (0x800000000000000);

static const BitBoard c_pawn_initial_board (0xff000000000000);

static const vector<PieceSet::piece_index_t> c_pawn_conversions = {
  PieceSet::ROOK_INDEX,
  PieceSet::BISHOP_INDEX,
  PieceSet::KNIGHT_INDEX,
  PieceSet::PAWN_INDEX
};

const Piece* PieceSet::rook() const
{
  return m_rook;
}

const Piece* PieceSet::knight() const
{
  return m_knight;
}

const Piece* PieceSet::bishop() const
{
  return m_bishop;
}

const Piece* PieceSet::queen() const
{
  return m_queen;
}

const Piece* PieceSet::king() const
{
  return m_king;
}

const Piece* PieceSet::pawn() const
{
  return m_pawn;
}

const vector<Piece*>& PieceSet::pieces() const
{
  return m_pieces;
}

PieceSet::PieceSet():
  m_rook (new LinePiece(ROOK_INDEX, c_rook_initial_board, c_rook_directions)),
  m_knight (new OncePiece(KNIGHT_INDEX, c_knight_initial_board, c_knight_directions)),
  m_bishop (new LinePiece(BISHOP_INDEX, c_bishop_initial_board, c_bishop_directions)),
  m_queen (new LinePiece(QUEEN_INDEX, c_queen_initial_board, c_queen_directions)),
  m_king (new OncePiece(KING_INDEX, c_king_initial_board, c_queen_directions)),
  m_pawn (new Pawn(PAWN_INDEX, c_pawn_initial_board, c_pawn_conversions))
{
  m_pieces.push_back(m_rook);
  m_pieces.push_back(m_knight);
  m_pieces.push_back(m_bishop);
  m_pieces.push_back(m_king);
  m_pieces.push_back(m_queen);
  m_pieces.push_back(m_pawn);
}

static PieceSet *INSTANCE = nullptr;

const PieceSet& PieceSet::instance()
{
  if (INSTANCE == nullptr) {
    INSTANCE = new PieceSet();
  }
  return *INSTANCE;
}
