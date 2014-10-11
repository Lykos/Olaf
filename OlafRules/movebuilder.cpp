#include "movebuilder.h"


#include "piecemoveaction.h"
#include "turnflipaction.h"
#include "epdisableaction.h"
#include "epenableaction.h"
#include "captureaction.h"
#include "anticastleaction.h"
#include "conversionaction.h"
#include "pieceset.h"
#include "move.h"
#include "moveaction.h"

using namespace std;

// static
Move MoveBuilder::castle(const ChessBoard& board,
                                const Position& source,
                                const Position& destination)
{
  MoveBuilder builder(board, source, destination);
  if (destination.column() == 2) {
    unique_ptr<MoveAction> rook_move_action(
          new PieceMoveAction(PieceSet::instance().rook().piece_index(),
                              Position(source.row(), 0),
                              Position(source.row(), 3)));
    builder.m_move_actions.push_back(move(rook_move_action));
  } else if (destination.column() == 6) {
    unique_ptr<MoveAction> rook_move_action(
          new PieceMoveAction(PieceSet::instance().rook().piece_index(),
                              Position(source.row(), 7),
                              Position(source.row(), 5)));
    builder.m_move_actions.push_back(move(rook_move_action));
  }
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
  unique_ptr<MoveAction> piece_move_action(
        new PieceMoveAction(piece_index, source, destination));
  unique_ptr<MoveAction> ep_disable_action(new EpDisableAction());
  m_move_actions.push_back(move(piece_move_action));
  m_move_actions.push_back(move(ep_disable_action));
  if (board.opponent(destination)) {
    unique_ptr<MoveAction> capture_action(
          new CaptureAction(destination,
                            board.noturn_board().piece_index(destination)));
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
  unique_ptr<MoveAction> turn_flip_action(new TurnFlipAction());
  m_move_actions.push_back(move(turn_flip_action));
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
  return result;
}
