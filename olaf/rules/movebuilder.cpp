#include "olaf/rules/movebuilder.h"

#include <algorithm>
#include <cassert>

#include "olaf/rules/piecemoveaction.h"
#include "olaf/rules/turnflipaction.h"
#include "olaf/rules/epdisableaction.h"
#include "olaf/rules/epenableaction.h"
#include "olaf/rules/captureaction.h"
#include "olaf/rules/anticastleaction.h"
#include "olaf/rules/conversionaction.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/move.h"
#include "olaf/rules/moveaction.h"
#include "olaf/rules/setkingcapturepositionsaction.h"

using namespace std;

namespace olaf
{

namespace {

bool CompareMoveActionPriorities(const unique_ptr<MoveAction>& left,
                                 const unique_ptr<MoveAction>& right)
{
  return left->priority() < right->priority();
}

} // namespace

// static
Move MoveBuilder::castle(const ChessBoard& board,
                         const Position& source,
                         const Position& destination)
{
  MoveBuilder builder(board, source, destination);
  Position::column_t rook_source_column;
  Position::column_t rook_destination_column;
  if (destination.column() == Position::c_queens_bishop_column) {
    rook_source_column = Position::c_queens_rook_column;
    rook_destination_column = Position::c_queen_column;
  } else {
    assert(destination.column() == Position::c_kings_knight_column);
    rook_source_column = Position::c_kings_rook_column;
    rook_destination_column = Position::c_kings_bishop_column;
  }
  Position rook_source(source.row(), rook_source_column);
  Position rook_destination(source.row(), rook_destination_column);
  unique_ptr<MoveAction> rook_move_action(
        new PieceMoveAction(PieceSet::instance().rook().piece_index(),
                            rook_source,
                            rook_destination));
  builder.m_move_actions.push_back(move(rook_move_action));
  const vector<Position> king_capture_positions{source, rook_destination};
  unique_ptr<MoveAction> set_king_capture_positions(
        new SetKingCapturePositionsAction(king_capture_positions, destination));
  builder.m_move_actions.push_back(move(set_king_capture_positions));
  builder.forbid_castling();
  return builder.build();
}

MoveBuilder::MoveBuilder(const MoveBuilder& builder):
  m_move_actions(builder.copy_move_actions()),
  m_source(builder.m_source),
  m_destination(builder.m_destination),
  m_conversion(builder.m_conversion),
  m_capture(builder.m_capture),
  m_created_piece(builder.m_created_piece)
{}

MoveBuilder::MoveBuilder(MoveBuilder&& builder):
  m_move_actions(move(builder.m_move_actions)),
  m_source(move(builder.m_source)),
  m_destination(move(builder.m_destination)),
  m_conversion(builder.m_conversion),
  m_capture(builder.m_capture),
  m_created_piece(builder.m_created_piece)
{}

MoveBuilder::~MoveBuilder()
{}

MoveBuilder::MoveBuilder(const ChessBoard& board,
                         const Position& source,
                         const Position& destination):
  m_source(source),
  m_destination(destination)
{
  const Piece::piece_index_t piece_index = board.turn_board().piece_index(source);
  unique_ptr<MoveAction> turn_flip_action(new TurnFlipAction());
  unique_ptr<MoveAction> piece_move_action(
        new PieceMoveAction(piece_index, source, destination));
  unique_ptr<MoveAction> ep_disable_action(new EpDisableAction());
  unique_ptr<MoveAction> set_king_capture_positions(
        new SetKingCapturePositionsAction(vector<Position>(), Position()));
  m_move_actions.push_back(move(turn_flip_action));
  m_move_actions.push_back(move(piece_move_action));
  m_move_actions.push_back(move(ep_disable_action));
  m_move_actions.push_back(move(set_king_capture_positions));
  if (board.opponent(destination)) {
    unique_ptr<MoveAction> capture_action(
          new CaptureAction(destination,
                            board.noturn_board().piece_index(destination)));
    m_move_actions.push_back(move(capture_action));
    m_capture = true;
  }
  const vector<Position> king_capture_positions = board.king_capture_positions();
  if (std::find(king_capture_positions.begin(),
                king_capture_positions.end(),
                destination) != king_capture_positions.end()) {
    unique_ptr<MoveAction> capture_action(
          new CaptureAction(board.king_victim_position(),
                            PieceSet::instance().king().piece_index()));
    m_move_actions.push_back(move(capture_action));
    m_capture = true;
  }
}

void MoveBuilder::enable_ep(const Position& capture_position)
{
  unique_ptr<MoveAction> ep_enable_action(new EpEnableAction(capture_position, m_destination));
  m_move_actions.push_back(move(ep_enable_action));
}

void MoveBuilder::capture_ep(const ChessBoard& board)
{
  unique_ptr<MoveAction> capture_action(
        new CaptureAction(board.ep_victim_position(),
                          PieceSet::instance().pawn().piece_index()));
  m_capture = true;
  m_move_actions.push_back(move(capture_action));
}

void MoveBuilder::forbid_castling()
{
  unique_ptr<MoveAction> anti_castle_action(new AntiCastleAction(true, true));
  m_move_actions.push_back(move(anti_castle_action));
}

void MoveBuilder::forbid_q_castling()
{
  unique_ptr<MoveAction> anti_castle_action(new AntiCastleAction(true, false));
  m_move_actions.push_back(move(anti_castle_action));
}

void MoveBuilder::forbid_k_castling()
{
  unique_ptr<MoveAction> anti_castle_action(new AntiCastleAction(false, true));
  m_move_actions.push_back(move(anti_castle_action));
}

void MoveBuilder::conversion(const Position& position,
                             const PieceSet::piece_index_t removed_piece,
                             const PieceSet::piece_index_t created_piece)
{
  unique_ptr<MoveAction> conversion_action(
        new ConversionAction(position, removed_piece, created_piece));
  m_move_actions.push_back(move(conversion_action));
  m_conversion = true;
  m_created_piece = created_piece;
}

Move MoveBuilder::build()
{
  return Move(copy_move_actions(),
              m_source,
              m_destination,
              m_capture,
              m_conversion,
              m_created_piece);
}

MoveActions MoveBuilder::copy_move_actions() const
{
  MoveActions result;
  for (const std::unique_ptr<MoveAction>& move_action : m_move_actions) {
    result.push_back(move_action->copy());
  }
  stable_sort(result.begin(), result.end(), CompareMoveActionPriorities);
  return result;

} // namespace olaf
}
