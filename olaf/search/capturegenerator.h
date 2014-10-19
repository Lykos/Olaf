#ifndef CAPTUREGENERATOR_H
#define CAPTUREGENERATOR_H

#include "olaf/search/movegenerator.h"
#include "olaf/rules/move.h"
#include <memory>
#include <vector>

namespace olaf
{

class CaptureGenerator : public MoveGenerator
{
public:
  CaptureGenerator(std::unique_ptr<MoveGenerator> generator);

  std::vector<Move> generate_moves(const ChessBoard& board) override;

  std::vector<Move> generate_valid_moves(const ChessBoard& board) override;

private:
  std::unique_ptr<MoveGenerator> m_generator;
};

} // namespace olaf

#endif // CAPTUREGENERATOR_H
