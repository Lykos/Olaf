#include "olaf/rules/pieceset.h"
#include "olaf/rules/bitboard.h"
#include <array>

using namespace std;

namespace olaf
{

static const BitBoard c_rook_initial_board(0x81ull);

static const BitBoard c_knight_initial_board(0x42ull);

static const BitBoard c_bishop_initial_board(0x24ull);

static const BitBoard c_queen_initial_board(0x8ull);

static const BitBoard c_king_initial_board(0x10ull);

static const BitBoard c_pawn_initial_board(0xff00ull);

static const PieceSet::PromotionArray c_pawn_conversions = {
  PieceSet::c_rook_index,
  PieceSet::c_bishop_index,
  PieceSet::c_knight_index,
  PieceSet::c_queen_index
};

const Piece& PieceSet::rook() const
{
  return *m_rook;
}

const Piece& PieceSet::knight() const
{
  return *m_knight;
}

const Piece& PieceSet::bishop() const
{
  return *m_bishop;
}

const Piece& PieceSet::queen() const
{
  return *m_queen;
}

const Piece& PieceSet::king() const
{
  return *m_king;
}

const Piece& PieceSet::pawn() const
{
  return *m_pawn;
}

const PieceSet::PieceArray& PieceSet::pieces() const
{
  return m_pieces;
}

const Piece& PieceSet::piece(const piece_index_t piece_index) const
{
  return *(m_pieces[piece_index]);
}

PieceSet::PieceSet():
  m_rook(new Piece(c_rook_index, 'r', c_rook_initial_board)),
  m_knight(new Piece(c_knight_index, 'n', c_knight_initial_board)),
  m_bishop(new Piece(c_bishop_index, 'b', c_bishop_initial_board)),
  m_queen(new Piece(c_queen_index, 'q', c_queen_initial_board)),
  m_king(new Piece(c_king_index, 'k', c_king_initial_board)),
  m_pawn(new Piece(c_pawn_index, 'p', c_pawn_initial_board))
{
  m_pieces[m_rook->piece_index()] = m_rook.get();
  m_pieces[m_knight->piece_index()] = m_knight.get();
  m_pieces[m_bishop->piece_index()] = m_bishop.get();
  m_pieces[m_queen->piece_index()] = m_queen.get();
  m_pieces[m_king->piece_index()] = m_king.get();
  m_pieces[m_pawn->piece_index()] = m_pawn.get();
}

const PieceSet& PieceSet::instance()
{
  static PieceSet instance;
  return instance;
}

} // namespace olaf
