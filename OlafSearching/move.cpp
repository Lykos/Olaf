#include "move.h"

#include <cassert>

#include "pieceset.h"

using namespace std;

static MoveActions copy_move_actions(const MoveActions& move_actions) {
  MoveActions result;
  for (const unique_ptr<MoveAction>& move_action : move_actions) {
    assert(move_action.get());
    result.push_back(move_action->copy());
  }
  return result;
}

Move::Move() {}

Move::Move(MoveActions&& move_actions,
           const Position& source,
           const Position& destination,
           const bool capture,
           const bool conversion,
           const Piece::piece_index_t created_piece):
  m_move_actions(move(move_actions)),
  m_source(source),
  m_destination(destination),
  m_conversion(conversion),
  m_capture(capture),
  m_created_piece(created_piece)
{}

Move::Move(const Move& move):
  m_move_actions(copy_move_actions(move.m_move_actions)),
  m_source(move.m_source),
  m_destination(move.m_destination),
  m_conversion(move.m_conversion),
  m_capture(move.m_capture),
  m_created_piece(move.m_created_piece)
{}

Move::Move(Move&& move):
  m_move_actions(std::move(move.m_move_actions)),
  m_source(std::move(move.m_source)),
  m_destination(std::move(move.m_destination)),
  m_conversion(move.m_conversion),
  m_capture(move.m_capture),
  m_created_piece(move.m_created_piece)
{}

Move& Move::operator =(const Move& move)
{
  m_move_actions = copy_move_actions(move.m_move_actions);
  m_source = move.m_source;
  m_destination = move.m_destination;
  m_conversion = move.m_conversion;
  m_capture = move.m_capture;
  m_created_piece = move.m_created_piece;
  return *this;
}

Move& Move::operator =(Move&& move)
{
  m_move_actions = std::move(move.m_move_actions);
  m_source = std::move(move.m_source);
  m_destination = std::move(move.m_destination);
  m_conversion = move.m_conversion;
  m_capture = move.m_capture;
  m_created_piece = move.m_created_piece;
  return *this;
}

Move::~Move()
{}

bool Move::is_valid(const ChessBoard& board) const
{
  const Piece::piece_index_t piece_index =
      board.turn_board().piece_index(m_source);
  if (piece_index == Piece::c_no_piece) {
    return false;
  }
  if (!m_conversion) {
    const bool result = board.turn_board().piece(m_source).can_move(m_source,
                                                       m_destination,
                                                       board);
    return result;
  } else {
    const Pawn& pawn = PieceSet::instance().pawn();
    const bool result = piece_index == pawn.piece_index()
        && pawn.can_move(m_source, m_destination, board, m_created_piece);
    return result;
  }
}

void Move::execute(ChessBoard* const board)
{
  assert(is_valid(*board));
  for (auto it = m_move_actions.begin(); it < m_move_actions.end(); ++it) {
    (*it)->execute(board);
  }
}

void Move::undo(ChessBoard* const board)
{
  for (auto it = m_move_actions.rbegin(); it < m_move_actions.rend(); ++it) {
    (*it)->undo(board);
  }
  assert(is_valid(*board));
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

std::ostream& operator <<(std::ostream& out, const Move& move)
{
  out << "Move(" << move.source() << " " << move.destination();
  if (move.is_capture()) {
    out << " capture";
  }
  if (move.is_conversion()) {
    out << " converts to " << move.created_piece();
  }
  return out << ")";
}
