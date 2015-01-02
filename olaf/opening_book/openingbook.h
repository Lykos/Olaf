#ifndef OPENINGBOOK_H
#define OPENINGBOOK_H

#include <cstdint>
#include <memory>
#include <string>
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

struct InternalOpeningBookEntry {
  std::uint64_t opening_zobrist_hash;
  std::uint16_t move;
  std::uint16_t weight;
  std::uint32_t learn;
};

class OpeningBook
{
public:
  static std::unique_ptr<OpeningBook> load(const std::string& book_file_name);

  OpeningBook();

  std::uint64_t opening_zobrist_hash(const ChessBoard& board) const;

  bool get(const ChessBoard& board, std::vector<OpeningBookEntry>* entries) const;

private:
  explicit OpeningBook(std::vector<InternalOpeningBookEntry>&& entries);

  const std::vector<InternalOpeningBookEntry> m_entries;
};

} // namespace olaf

#endif // OPENINGBOOK_H

