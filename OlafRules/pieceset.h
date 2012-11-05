#ifndef PIECESET_H
#define PIECESET_H

#include "piece.h"
#include "pawn.h"
#include <vector>
#include <memory>

class PieceSet
{
public:
  typedef Piece::piece_index_t piece_index_t;

  PieceSet(PieceSet&& that) = delete;

  PieceSet(const PieceSet& that) = delete;

  PieceSet& operator=(PieceSet&& that) = delete;

  PieceSet& operator=(const PieceSet& that) = delete;

  const std::shared_ptr<const Piece>& rook() const;

  const std::shared_ptr<const Piece>& knight() const;

  const std::shared_ptr<const Piece>& bishop() const;

  const std::shared_ptr<const Piece>& queen() const;

  const std::shared_ptr<const Piece>& king() const;

  const std::shared_ptr<const Pawn>& pawn() const;

  const std::vector< std::shared_ptr<const Piece> >& pieces() const;

  static const PieceSet& instance();

private:
  PieceSet();

  std::shared_ptr<const Piece> m_rook;

  std::shared_ptr<const Piece> m_knight;

  std::shared_ptr<const Piece> m_bishop;

  std::shared_ptr<const Piece> m_queen;

  std::shared_ptr<const Piece> m_king;

  std::shared_ptr<const Pawn> m_pawn;

  std::vector< std::shared_ptr<const Piece> > m_pieces;

};

#endif // PIECESET_H
