#include "move.h"
#include "piecemoveaction.h"
#include "turnflipaction.h"
#include "epdisableaction.h"
#include "epenablaction.h"
#include "captureaction.h"
#include "anticastleaction.h"
#include "conversionaction.h"

using namespace std;

Move::Move(PieceSet::piece_index_t piece_index, const Position &source, const Position &destination)
{
  m_move_ptrs.push_back(new PieceMoveAction(piece_index, source, destination));
  m_move_ptrs.push_back(new TurnFlipAction());
}

void Move::enable_ep(const Position& capture_position, const Position& victim_position)
{
  m_move_ptrs.push_back(new EpEnableAction(capture_position, victim_position));
}

void Move::disable_ep()
{
  m_move_ptrs.push_back(new EpDisableAction());
}

void Move::capture(PieceSet::piece_index_t piece_index, const Position& victim_position)
{
  m_move_ptrs.push_back(new CaptureAction(victim_position, piece_index));
}

void Move::forbid_castling()
{
  m_move_ptrs.push_back(new AntiCastleAction(true, true));
}

void Move::forbid_q_castling()
{
  m_move_ptrs.push_back(new AntiCastleAction(true, false));
}

void Move::forbid_k_castling()
{
  m_move_ptrs.push_back(new AntiCastleAction(false, true));
}

void Move::conversion(const Position &position, PieceSet::piece_index_t removed_piece, PieceSet::piece_index_t created_piece)
{
  m_move_ptrs.push_back(new ConversionAction(position, removed_piece, created_piece));
}

void Move::execute(ChessBoard& chess_board)
{
  for (auto it = m_move_ptrs.begin(); it < m_move_ptrs.end(); ++it) {
    (*it)->execute(chess_board);
  }
  chess_board.flip_turn();
}

void Move::undo(ChessBoard& chess_board)
{
  chess_board.flip_turn();
  for (auto it = m_move_ptrs.begin(); it < m_move_ptrs.end(); ++it) {
    (*it)->undo(chess_board);
  }
}

Move::~Move()
{
  for (auto it = m_move_ptrs.begin(); it < m_move_ptrs.end(); ++it) {
    delete *it;
  }
}
