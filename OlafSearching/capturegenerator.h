#ifndef CAPTUREGENERATOR_H
#define CAPTUREGENERATOR_H

#include "movegenerator.h"
#include "OlafRules/move.h"
#include <memory>
#include <vector>

class CaptureGenerator : public MoveGenerator
{
public:
  CaptureGenerator(const std::shared_ptr<MoveGenerator> &generator);

  std::vector<Move> generate_moves(const ChessBoard &board);

private:
  std::shared_ptr<MoveGenerator> m_generator;

};

#endif // CAPTUREGENERATOR_H
