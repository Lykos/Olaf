#include "move.h"
#include "piecemoveaction.h"
#include "turnflipaction.h"
#include "epdisableaction.h"
#include "epenablaction.h"
#include "captureaction.h"
#include "anticastleaction.h"
#include "conversionaction.h"
#include "pieceset.h"

using namespace std;

Move::Move()
{}

Move::Move(const ChessBoard& board, Piece::piece_index_t piece_index, const Position &source, const Position &destination):
  m_source (source),
  m_destination (destination)
{
  shared_ptr<MoveAction> piece_move_action(new PieceMoveAction(piece_index, source, destination));
  shared_ptr<MoveAction> turn_flip_action(new TurnFlipAction());
  shared_ptr<MoveAction> ep_disable_action(new EpDisableAction());
  m_move_actions.push_back(piece_move_action);
  m_move_actions.push_back(turn_flip_action);
  m_move_actions.push_back(ep_disable_action);
  if (board.opponent(destination)) {
    shared_ptr<MoveAction> capture_action(new CaptureAction(destination, board.noturn_board().piece_index(destination)));
    m_move_actions.push_back(capture_action);
    m_capture = true;
  }
}

Move::Move(const ChessBoard& board, Piece::piece_index_t piece_index, const Position &source, const Position &destination, const Position &capture_position):
  Move(board, piece_index, source, destination)
{
  shared_ptr<MoveAction> ep_enable_action(new EpEnableAction(capture_position, destination));
  m_move_actions.push_back(ep_enable_action);
}

Move::Move(const ChessBoard &board, const Position &source, const Position &destination):
  Move(board, PieceSet::instance().king()->piece_index(), source, destination)
{
  if (destination.column() == 2) {
    shared_ptr<MoveAction> rook_move_action (new PieceMoveAction(PieceSet::instance().rook()->piece_index(), Position(source.row(), 0), Position(source.row(), 3)));
    m_move_actions.push_back(rook_move_action);
  } else if (destination.column() == 6) {
    shared_ptr<MoveAction> rook_move_action (new PieceMoveAction(PieceSet::instance().rook()->piece_index(), Position(source.row(), 7), Position(source.row(), 5)));
    m_move_actions.push_back(rook_move_action);
  }
  forbid_castling();
}

void Move::capture_ep(const ChessBoard &board)
{
  shared_ptr<MoveAction> capture_action (new CaptureAction(board.ep_victim_position(), PieceSet::instance().pawn()->piece_index()));
  m_capture = true;
  m_move_actions.push_back(capture_action);
}

void Move::forbid_castling()
{
  shared_ptr<MoveAction> anti_castle_action (new AntiCastleAction(true, true));
  m_move_actions.push_back(anti_castle_action);
}

void Move::forbid_q_castling()
{
  shared_ptr<MoveAction> anti_castle_action (new AntiCastleAction(true, false));
  m_move_actions.push_back(anti_castle_action);
}

void Move::forbid_k_castling()
{
  shared_ptr<MoveAction> anti_castle_action (new AntiCastleAction(false, true));
  m_move_actions.push_back(anti_castle_action);
}

void Move::conversion(const Position &position, PieceSet::piece_index_t removed_piece, PieceSet::piece_index_t created_piece)
{
  shared_ptr<MoveAction> conversion_action (new ConversionAction(position, removed_piece, created_piece));
  m_move_actions.push_back(conversion_action);
  m_conversion = true;
  m_created_piece = created_piece;
}

void Move::execute(ChessBoard& chess_board)
{
  for (auto it = m_move_actions.begin(); it < m_move_actions.end(); ++it) {
    (*it)->execute(chess_board);
  }
  chess_board.flip_turn();
}

void Move::undo(ChessBoard& chess_board)
{
  chess_board.flip_turn();
  for (auto it = m_move_actions.begin(); it < m_move_actions.end(); ++it) {
    (*it)->undo(chess_board);
  }
}

const Position& Move::source() const
{
  return m_source;
}

const Position& Move::destination() const
{
  return m_destination;
}

bool Move::is_capture() const
{
  return m_capture;
}

bool Move::is_conversion() const
{
  return m_conversion;
}

Piece::piece_index_t Move::created_piece() const
{
  return m_created_piece;
}
