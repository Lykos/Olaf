#include "olaf/search/capturegenerator.h"

using namespace std;

namespace olaf
{

static vector<Move> filter_captures(const vector<Move>& candidates)
{
  vector<Move> result;
  for (const Move& move : candidates) {
    if (move.is_capture()) {
      result.push_back(move);
    }
  }
  return result;
}

CaptureGenerator::CaptureGenerator(unique_ptr<MoveGenerator> generator):
  m_generator(move(generator))
{}

vector<Move> CaptureGenerator::generate_moves(const ChessBoard& board)
{
  return filter_captures(m_generator->generate_moves(board));
}

vector<Move> CaptureGenerator::generate_valid_moves(const ChessBoard& board)
{
  return filter_captures(m_generator->generate_valid_moves(board));

} // namespace olaf
}
