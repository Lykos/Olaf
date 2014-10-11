#include "capturegenerator.h"

using namespace std;

CaptureGenerator::CaptureGenerator(unique_ptr<MoveGenerator> generator):
  m_generator(move(generator))
{}

vector<Move> CaptureGenerator::generate_moves(const ChessBoard &board)
{
  vector<Move> result;
  vector<Move> candidates = m_generator->generate_moves(board);
  for (const Move &move : candidates) {
    if (move.is_capture()) {
      result.push_back(move);
    }
  }
  return result;
}
