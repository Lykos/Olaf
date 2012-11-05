#include "capturegenerator.h"
#include <iostream>

using namespace std;

CaptureGenerator::CaptureGenerator(const shared_ptr<MoveGenerator> &generator):
  m_generator (generator)
{}

vector<Move> CaptureGenerator::generate_moves(const ChessBoard &board)
{
  vector<Move> result;
  vector<Move> candidates = m_generator->generate_moves(board);
  for (const Move &move : candidates) {
    if (move.is_capture()) {
      result.push_back(move);
      cout << "# capture generator takes " << move.source() << " " << move.destination() << endl;
    } else {
      cout << "# capture generator ignores " << move.source() << " " << move.destination() << endl;
    }
  }
  return result;
}
