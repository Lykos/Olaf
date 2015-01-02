#ifndef OPENINGBOOK_H
#define OPENINGBOOK_H

#include <cstdint>
#include <vector>

#include "olaf/rules/move.h"
#include "olaf/rules/chessboard.h"

namespace olaf
{

struct OpeningBookEntry {
  Move move;
  std::uint16_t weight;
  std::uint32_t learn;
};

class OpeningBook
{
public:
  std::uint64_t opening_zobrist_hash(const ChessBoard& board) const;

  bool get(const ChessBoard& board, OpeningBookEntry* entry) const;

private:
  struct InternalOpeningBookEntry {
    std::uint64_t opening_zobrist_hash;
    std::uint16_t move;
    std::uint16_t weight;
    std::uint32_t learn;
  };

  const std::vector<InternalOpeningBookEntry> m_entries;
};

} // namespace olaf

#endif // OPENINGBOOK_H

