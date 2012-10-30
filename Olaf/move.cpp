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
  m_move_actions.push_back(new PieceMoveAction(piece_index, source, destination));
  m_move_actions.push_back(new TurnFlipAction());
  m_move_actions.push_back(new EpDisableAction());
  if (board.opponent(destination)) {
    m_move_actions.push_back(new CaptureAction(destination, board.noturn_board().piece_index(destination)));
  }

}

Move::Move(const ChessBoard& board, Piece::piece_index_t piece_index, const Position &source, const Position &destination, const Position &capture_position):
  Move(board, piece_index, source, destination)
{
  m_move_actions.push_back(new EpEnableAction(capture_position, destination));
}

Move::Move(const ChessBoard &board, const Position &source, const Position &destination):
  Move(board, PieceSet::instance().king()->piece_index(), source, destination)
{
  if (destination.column() == 2) {
    m_move_actions.push_back(new PieceMoveAction(PieceSet::instance().rook()->piece_index(), Position(source.row(), 0), Position(source.row(), 3)));
  } else if (destination.column() == 6) {
    m_move_actions.push_back(new PieceMoveAction(PieceSet::instance().rook()->piece_index(), Position(source.row(), 7), Position(source.row(), 5)));
  }
  forbid_castling();
}

void Move::capture(const ChessBoard &board)
{
  m_move_actions.push_back(new CaptureAction(board.ep_position(), PieceSet::instance().pawn()->piece_index()));
}

void Move::forbid_castling()
{
  m_move_actions.push_back(new AntiCastleAction(true, true));
}

void Move::forbid_q_castling()
{
  m_move_actions.push_back(new AntiCastleAction(true, false));
}

void Move::forbid_k_castling()
{
  m_move_actions.push_back(new AntiCastleAction(false, true));
}

void Move::conversion(const Position &position, PieceSet::piece_index_t removed_piece, PieceSet::piece_index_t created_piece)
{
  m_move_actions.push_back(new ConversionAction(position, removed_piece, created_piece));
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

bool Move::is_conversion() const
{
  return m_conversion;
}

Piece::piece_index_t Move::created_piece() const
{
  return m_created_piece;
}

Move::~Move()
{
  for (auto it = m_move_actions.begin(); it < m_move_actions.end(); ++it) {
    delete *it;
  }
}
