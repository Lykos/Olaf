#ifndef PIECESET_H
#define PIECESET_H

#include <array>
#include <memory>

#include "olaf/rules/piece.h"

namespace olaf
{

class Pawn;

class PieceSet
{
public:
  typedef Piece::piece_index_t piece_index_t;

  PieceSet(PieceSet&& that) = delete;

  PieceSet(const PieceSet& that) = delete;

  PieceSet& operator=(PieceSet&& that) = delete;

  PieceSet& operator=(const PieceSet& that) = delete;

  static const piece_index_t c_rook_index = 0;

  static const piece_index_t c_knight_index = 1;

  static const piece_index_t c_bishop_index = 2;

  static const piece_index_t c_queen_index = 3;

  static const piece_index_t c_king_index = 4;

  static const piece_index_t c_pawn_index = 5;

  static const piece_index_t c_no_pieces = 6;

  static const piece_index_t c_no_promotions = 4;

  typedef std::array<const Piece*, PieceSet::c_no_pieces> PieceArray;

  typedef std::array<piece_index_t, PieceSet::c_no_promotions> PromotionArray;

  const Piece& rook() const;

  const Piece& knight() const;

  const Piece& bishop() const;

  const Piece& queen() const;

  const Piece& king() const;

  const Pawn& pawn() const;

  const PieceArray& pieces() const;

  const Piece& piece(piece_index_t piece_index) const;

  static const PieceSet& instance();

private:
  PieceSet();

  std::unique_ptr<const Piece> m_rook;

  std::unique_ptr<const Piece> m_knight;

  std::unique_ptr<const Piece> m_bishop;

  std::unique_ptr<const Piece> m_queen;

  std::unique_ptr<const Piece> m_king;

  std::unique_ptr<const Pawn> m_pawn;

  PieceArray m_pieces;

};

} // namespace olaf

#endif // PIECESET_H
