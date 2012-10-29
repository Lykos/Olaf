#include "simplemoveaction.h"
#include <vector>

using namespace std;

SimpleMoveAction::SimpleMoveAction(ColorBoard::piece_index_t piece_index, const Position &source, const Position &destination):
  m_piece_index (piece_index),
  m_source (source),
  m_destination (destination)
{}

void SimpleMoveAction::execute(ChessBoard& chess_board)
{
  m_old_ep_possible = chess_board.ep_possible();
  m_capture = false;
  vector<PieceBoard> opponent_pieces = chess_board.noturn_board().piece_boards();
  m_victim_position = m_destination;
  if (m_destination == chess_board.ep_capture_position()) {
    m_victim_position = chess_board.ep_victim_position();
  }
  for (m_victim_index = 0; m_victim_index < opponent_pieces.size(); ++m_victim_index) {
    if (opponent_pieces[m_victim_index].get(m_victim_position)) {
      m_capture = true;
      opponent_pieces[m_victim_index].set(m_victim_position, false);
      break;
    }
  }
  chess_board.turn_board().piece_board(m_piece_index).set(m_source, false);
  chess_board.ep_possible(false);
}

void SimpleMoveAction::undo(ChessBoard& chess_board)
{
  chess_board.ep_possible(m_old_ep_possible);
  chess_board.turn_board().piece_board(m_piece_index).set(m_source, true);
  if (m_capture) {
    chess_board.noturn_board().piece_board(m_victim_index).set(m_victim_position, true);
  }
}
