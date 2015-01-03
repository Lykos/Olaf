#include "olaf/evaluation/kingsafetyevaluator.h"

#include <array>

#include "olaf/evaluation/incrementalupdater.h"
#include "olaf/rules/magicmoves.h"

using namespace std;

namespace olaf
{

typedef array<BitBoard, c_no_colors * BitBoard::c_bitboard_size> BitBoardArray;

static const BitBoardArray c_pawn_shield = {
  0x70700, 0x70700, 0xe0e00, 0x1c1c00, 0x383800, 0x707000, 0xe0e000, 0xe0e000,
  0x70700, 0x70700, 0xe0e00, 0x1c1c00, 0x383800, 0x707000, 0xe0e000, 0xe0e000,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0x7070000000000, 0x7070000000000, 0xe0e0000000000, 0x1c1c0000000000,
  0x38380000000000, 0x70700000000000, 0xe0e00000000000, 0xe0e00000000000,
  0x7070000000000, 0x7070000000000, 0xe0e0000000000, 0x1c1c0000000000,
  0x38380000000000, 0x70700000000000, 0xe0e00000000000, 0xe0e00000000000
};

static const PositionEvaluator::score_t c_pawn_shield_score = 10;

static PositionEvaluator::score_t pawn_shield_score(const ChessBoard& board,
                                                    const Position king_position,
                                                    const Color color)
{
  const int color_index = static_cast<int>(color) * BitBoard::c_bitboard_size;
  const BitBoard potential_pawn_shield(c_pawn_shield[color_index + king_position.index()]);
  const BitBoard pawn_shield = potential_pawn_shield & board.pawn_board(color);
  return pawn_shield.number() * c_pawn_shield_score;
}

static const PositionEvaluator::score_t c_own_semi_open_file_score = -12;
static const PositionEvaluator::score_t c_opposing_semi_open_file_score = -8;

static PositionEvaluator::score_t column_score(const ChessBoard& board, const Color color, const Position::index_t column)
{
  const BitBoard opponent_pawns = board.pawn_board(other_color(color));
  const BitBoard friend_pawns = board.pawn_board(other_color(color));
  const BitBoard column_board = c_columns[column];
  return ((column_board & friend_pawns) == BitBoard(0)) * c_own_semi_open_file_score
      + ((column_board & opponent_pawns) == BitBoard(0)) * c_opposing_semi_open_file_score;
}

static PositionEvaluator::score_t open_files_score(const ChessBoard& board,
                                                   const Position king_position,
                                                   const Color color)
{
  const Position::index_t column = king_position.column();
  if (column == 0) {
    return column_score(board, color, column) + column_score(board, color, column + 1);
  } else if (column == Position::c_column_size - 1) {
    return column_score(board, color, column - 1) + column_score(board, color, column);
  } else {
    return column_score(board, color, column - 1) + column_score(board, color, column) + column_score(board, color, column + 1);
  }
}

static const array<PositionEvaluator::score_t, c_no_colors * BitBoard::c_bitboard_size> c_initial_counters = {
  2, 0, 0, 0, 0, 0, 0, 2,
  2, 1, 1, 1, 1, 1, 1, 1,
  4, 3, 3, 3, 3, 3, 3, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,

  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 3, 3, 3, 3, 3, 3, 4,
  2, 1, 1, 1, 1, 1, 1, 1,
  2, 0, 0, 0, 0, 0, 0, 2
};

static const array<PositionEvaluator::score_t, 200> c_counter_values = {
    0,  2,  3,  6, 12, 18, 25, 37, 50, 75,
  100,125,150,175,200,225,250,275,300,325,
  350,375,400,425,450,475,500,525,550,575,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
  600,600,600,600,600,600,600,600,600,600,
};

static const array<PositionEvaluator::score_t, 32> c_attack_pattern_values = {
//. P N N R R R R Q Q Q Q Q Q Q Q K K K K K K K K K K K K K K K K
//      P   P N N   P N N R R R R   P N N R R R R Q Q Q Q Q Q Q Q
//              P       P   N N N       P   P N N   P N N R R R R
  0,0,0,0,0,0,1,1,0,1,2,2,2,3,3,3,0,0,0,0,1,1,2,2,2,3,3,3,3,3,3,3
};

static const BitBoardArray c_king_area = {
  0x303, 0x707, 0xe0e, 0x1c1c, 0x3838, 0x7070, 0xe0e0, 0xc0c0,
  0x30303, 0x70707, 0xe0e0e, 0x1c1c1c, 0x383838, 0x707070, 0xe0e0e0, 0xc0c0c0,
  0x3030300, 0x7070700, 0xe0e0e00, 0x1c1c1c00, 0x38383800, 0x70707000, 0xe0e0e000, 0xc0c0c000,
  0x303030000, 0x707070000, 0xe0e0e0000, 0x1c1c1c0000, 0x3838380000, 0x7070700000, 0xe0e0e00000, 0xc0c0c00000,
  0x30303000000, 0x70707000000, 0xe0e0e000000, 0x1c1c1c000000, 0x383838000000, 0x707070000000, 0xe0e0e0000000, 0xc0c0c0000000,
  0x3030300000000, 0x7070700000000, 0xe0e0e00000000, 0x1c1c1c00000000, 0x38383800000000, 0x70707000000000, 0xe0e0e000000000, 0xc0c0c000000000,
  0x303030000000000, 0x707070000000000, 0xe0e0e0000000000, 0x1c1c1c0000000000, 0x3838380000000000, 0x7070700000000000, 0xe0e0e00000000000, 0xc0c0c00000000000,
  0x303000000000000, 0x707000000000000, 0xe0e000000000000, 0x1c1c000000000000, 0x3838000000000000, 0x7070000000000000, 0xe0e0000000000000, 0xc0c0000000000000,

  0x303, 0x707, 0xe0e, 0x1c1c, 0x3838, 0x7070, 0xe0e0, 0xc0c0,
  0x30303, 0x70707, 0xe0e0e, 0x1c1c1c, 0x383838, 0x707070, 0xe0e0e0, 0xc0c0c0,
  0x3030300, 0x7070700, 0xe0e0e00, 0x1c1c1c00, 0x38383800, 0x70707000, 0xe0e0e000, 0xc0c0c000,
  0x303030000, 0x707070000, 0xe0e0e0000, 0x1c1c1c0000, 0x3838380000, 0x7070700000, 0xe0e0e00000, 0xc0c0c00000,
  0x30303000000, 0x70707000000, 0xe0e0e000000, 0x1c1c1c000000, 0x383838000000, 0x707070000000, 0xe0e0e0000000, 0xc0c0c0000000,
  0x3030300000000, 0x7070700000000, 0xe0e0e00000000, 0x1c1c1c00000000, 0x38383800000000, 0x70707000000000, 0xe0e0e000000000, 0xc0c0c000000000,
  0x303030000000000, 0x707070000000000, 0xe0e0e0000000000, 0x1c1c1c0000000000, 0x3838380000000000, 0x7070700000000000, 0xe0e0e00000000000, 0xc0c0c00000000000,
  0x303000000000000, 0x707000000000000, 0xe0e000000000000, 0x1c1c000000000000, 0x3838000000000000, 0x7070000000000000, 0xe0e0000000000000, 0xc0c0000000000000
};

static const BitBoardArray c_front_squares = {
  0x300, 0x700, 0xe00, 0x1c00, 0x3800, 0x7000, 0xe000, 0xc000,
  0x30000, 0x70000, 0xe0000, 0x1c0000, 0x380000, 0x700000, 0xe00000, 0xc00000,
  0x3000000, 0x7000000, 0xe000000, 0x1c000000, 0x38000000, 0x70000000, 0xe0000000, 0xc0000000,
  0x300000000, 0x700000000, 0xe00000000, 0x1c00000000, 0x3800000000, 0x7000000000, 0xe000000000, 0xc000000000,
  0x30000000000, 0x70000000000, 0xe0000000000, 0x1c0000000000, 0x380000000000, 0x700000000000, 0xe00000000000, 0xc00000000000,
  0x3000000000000, 0x7000000000000, 0xe000000000000, 0x1c000000000000, 0x38000000000000, 0x70000000000000, 0xe0000000000000, 0xc0000000000000,
  0x300000000000000, 0x700000000000000, 0xe00000000000000, 0x1c00000000000000, 0x3800000000000000, 0x7000000000000000, 0xe000000000000000, 0xc000000000000000,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,

  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x3, 0x7, 0xe, 0x1c, 0x38, 0x70, 0xe0, 0xc0,
  0x300, 0x700, 0xe00, 0x1c00, 0x3800, 0x7000, 0xe000, 0xc000,
  0x30000, 0x70000, 0xe0000, 0x1c0000, 0x380000, 0x700000, 0xe00000, 0xc00000,
  0x3000000, 0x7000000, 0xe000000, 0x1c000000, 0x38000000, 0x70000000, 0xe0000000, 0xc0000000,
  0x300000000, 0x700000000, 0xe00000000, 0x1c00000000, 0x3800000000, 0x7000000000, 0xe000000000, 0xc000000000,
  0x30000000000, 0x70000000000, 0xe0000000000, 0x1c0000000000, 0x380000000000, 0x700000000000, 0xe00000000000, 0xc00000000000,
  0x3000000000000, 0x7000000000000, 0xe000000000000, 0x1c000000000000, 0x38000000000000, 0x70000000000000, 0xe0000000000000, 0xc0000000000000
};

static const BitBoardArray c_relevant_squares = {
  0x30303, 0x70707, 0xe0e0e, 0x1c1c1c, 0x383838, 0x707070, 0xe0e0e0, 0xc0c0c0,
  0x3030303, 0x7070707, 0xe0e0e0e, 0x1c1c1c1c, 0x38383838, 0x70707070, 0xe0e0e0e0, 0xc0c0c0c0,
  0x303030300, 0x707070700, 0xe0e0e0e00, 0x1c1c1c1c00, 0x3838383800, 0x7070707000, 0xe0e0e0e000, 0xc0c0c0c000,
  0x30303030000, 0x70707070000, 0xe0e0e0e0000, 0x1c1c1c1c0000, 0x383838380000, 0x707070700000, 0xe0e0e0e00000, 0xc0c0c0c00000,
  0x3030303000000, 0x7070707000000, 0xe0e0e0e000000, 0x1c1c1c1c000000, 0x38383838000000, 0x70707070000000, 0xe0e0e0e0000000, 0xc0c0c0c0000000,
  0x303030300000000, 0x707070700000000, 0xe0e0e0e00000000, 0x1c1c1c1c00000000, 0x3838383800000000, 0x7070707000000000, 0xe0e0e0e000000000, 0xc0c0c0c000000000,
  0x303030000000000, 0x707070000000000, 0xe0e0e0000000000, 0x1c1c1c0000000000, 0x3838380000000000, 0x7070700000000000, 0xe0e0e00000000000, 0xc0c0c00000000000,
  0x303000000000000, 0x707000000000000, 0xe0e000000000000, 0x1c1c000000000000, 0x3838000000000000, 0x7070000000000000, 0xe0e0000000000000, 0xc0c0000000000000,

  0x303, 0x707, 0xe0e, 0x1c1c, 0x3838, 0x7070, 0xe0e0, 0xc0c0,
  0x30303, 0x70707, 0xe0e0e, 0x1c1c1c, 0x383838, 0x707070, 0xe0e0e0, 0xc0c0c0,
  0x3030303, 0x7070707, 0xe0e0e0e, 0x1c1c1c1c, 0x38383838, 0x70707070, 0xe0e0e0e0, 0xc0c0c0c0,
  0x303030300, 0x707070700, 0xe0e0e0e00, 0x1c1c1c1c00, 0x3838383800, 0x7070707000, 0xe0e0e0e000, 0xc0c0c0c000,
  0x30303030000, 0x70707070000, 0xe0e0e0e0000, 0x1c1c1c1c0000, 0x383838380000, 0x707070700000, 0xe0e0e0e00000, 0xc0c0c0c00000,
  0x3030303000000, 0x7070707000000, 0xe0e0e0e000000, 0x1c1c1c1c000000, 0x38383838000000, 0x70707070000000, 0xe0e0e0e0000000, 0xc0c0c0c0000000,
  0x303030300000000, 0x707070700000000, 0xe0e0e0e00000000, 0x1c1c1c1c00000000, 0x3838383800000000, 0x7070707000000000, 0xe0e0e0e000000000, 0xc0c0c0c000000000,
  0x303030000000000, 0x707070000000000, 0xe0e0e0000000000, 0x1c1c1c0000000000, 0x3838380000000000, 0x7070700000000000, 0xe0e0e00000000000, 0xc0c0c00000000000
};

class KingSafetyCalculator {
public:
  explicit inline KingSafetyCalculator(const Color color,
                                       const Position king_position,
                                       const BitBoard friends):
    m_friends(friends)
  {
    const int color_index = static_cast<int>(color) * BitBoard::c_bitboard_size;
    const int king_index = color_index + king_position.index();
    m_king_area = c_king_area[king_index];
    m_front_squares = c_front_squares[king_index];
    m_relevant_squares = c_relevant_squares[king_index];
    m_counter = c_initial_counters[king_index];
  }

  inline void opponent_attacks(const BitBoard attacks, const uint_fast8_t flag)
  {
    const BitBoard relevant_attacks = attacks & m_relevant_squares;
    if (relevant_attacks) {
      m_flag |= flag;
    }
    m_opponent_attacks = m_opponent_attacks | attacks;
  }

  inline void own_attacks(const BitBoard attacks)
  {
    m_own_attacks = m_own_attacks | attacks;
  }

  inline PositionEvaluator::score_t score() const
  {
    PositionEvaluator::score_t counter = m_counter;
    // Bonus for the attack pattern.
    counter += c_attack_pattern_values[m_flag];
    const BitBoard relevant_opponent_attacks = m_opponent_attacks & m_king_area;
    // Bonus for the attacked empty squares in front of the king.
    counter += (~m_friends & m_front_squares & m_opponent_attacks).number();
    // Bonus for the attacked squares around the king.
    counter += relevant_opponent_attacks.number();
    // Bonus for the attacked undefendend squares around the king.
    counter += (relevant_opponent_attacks & ~m_own_attacks).number();
    return c_counter_values[counter];
  }
private:
  uint_fast8_t m_flag = 0;
  const BitBoard m_friends;
  BitBoard m_king_area;
  BitBoard m_front_squares;
  BitBoard m_relevant_squares;
  BitBoard m_own_attacks;
  BitBoard m_opponent_attacks;
  int m_counter;
};

static const uint_fast8_t c_pawn_flag = 1;
static const uint_fast8_t c_knight_flag = 1 << 1;
// Ignored for attack patterns.
static const uint_fast8_t c_bishop_flag = 0;
static const uint_fast8_t c_rook_flag = 1 << 2;
static const uint_fast8_t c_queen_flag = 1 << 3;
static const uint_fast8_t c_king_flag = 1 << 4;

struct ColorAttacks {
  BitBoard pawns;
  BitBoard knights;
  BitBoard bishops;
  BitBoard rooks;
  BitBoard queens;
  BitBoard kings;
};

static inline void calculate_attacks(const ChessBoard& board,
                                     const Color color,
                                     ColorAttacks* const attacks)
{
  BitBoard pawns = board.pawn_board(color);
  while (pawns) {
    attacks->pawns = attacks->pawns | MagicMoves::moves_pawn(pawns.next_position(), board);
  }
  BitBoard knights = board.knight_board(color);
  while (knights) {
    attacks->knights = attacks->knights | MagicMoves::moves_knight(knights.next_position(), board);
  }
  BitBoard bishops = board.bishop_board(color);
  while (bishops) {
    attacks->bishops = attacks->bishops | MagicMoves::moves_bishop(bishops.next_position(), board);
  }
  BitBoard rooks = board.rook_board(color);
  while (rooks) {
    attacks->rooks = attacks->rooks | MagicMoves::moves_rook(rooks.next_position(), board);
  }
  BitBoard queens = board.queen_board(color);
  while (queens) {
    attacks->queens = attacks->queens | MagicMoves::moves_queen(queens.next_position(), board);
  }
  BitBoard kings = board.king_board(color);
  attacks->kings = MagicMoves::moves_king(kings.first_position(), board);
}

static inline PositionEvaluator::score_t attack_score(const ChessBoard& board,
                                                      const Position king_position,
                                                      const Color color,
                                                      const ColorAttacks& own_attacks,
                                                      const ColorAttacks& opponent_attacks)
{
  const BitBoard friends = board.turn_color() == color ? board.friends() : board.opponents();
  KingSafetyCalculator calculator(color, king_position, friends);

  calculator.own_attacks(own_attacks.pawns);
  calculator.own_attacks(own_attacks.knights);
  calculator.own_attacks(own_attacks.bishops);
  calculator.own_attacks(own_attacks.rooks);
  calculator.own_attacks(own_attacks.queens);

  calculator.opponent_attacks(opponent_attacks.pawns, c_pawn_flag);
  calculator.opponent_attacks(opponent_attacks.knights, c_knight_flag);
  calculator.opponent_attacks(opponent_attacks.bishops, c_bishop_flag);
  calculator.opponent_attacks(opponent_attacks.rooks, c_rook_flag);
  calculator.opponent_attacks(opponent_attacks.queens, c_queen_flag);
  calculator.opponent_attacks(opponent_attacks.kings, c_king_flag);

  return calculator.score();
}

static inline PositionEvaluator::score_t king_safety_score(const ChessBoard& board,
                                                           const Color color,
                                                           const ColorAttacks& own_attacks,
                                                           const ColorAttacks& opponent_attacks)
{
  const Position king_position = board.king_board(color).first_position();
  const PositionEvaluator::score_t score =
      pawn_shield_score(board, king_position, color)
      + open_files_score(board, king_position, color);
      + attack_score(board, king_position, color, own_attacks, opponent_attacks);
  return score;
}

PositionEvaluator::score_t KingSafetyEvaluator::evaluate(
    SearchState* const /* state */, SearchContext* const context)
{
  const ChessBoard& board = context->board;
  ColorAttacks turn_attacks;
  calculate_attacks(board, board.turn_color(), &turn_attacks);
  ColorAttacks noturn_attacks;
  calculate_attacks(board, board.noturn_color(), &noturn_attacks);
  const score_t score =
      king_safety_score(board, board.turn_color(), turn_attacks, noturn_attacks)
      - king_safety_score(board, board.noturn_color(), noturn_attacks, turn_attacks);
  return IncrementalUpdater::weighted_score(score, 0, board.incremental_state().material_score);
}

} // namespace olaf
