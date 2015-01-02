#include "olaf/evaluation/pawnevaluator.h"

#include "olaf/transposition_table/pawntable.h"

using namespace std;

namespace olaf
{

class ScoreCalculator
{
public:
  typedef PositionEvaluator::score_t score_t;

  constexpr explicit ScoreCalculator(const score_t initial_score = 0): m_score(initial_score)
  {}

  inline void add_score_white(const score_t score)
  {
    m_score += score;
  }

  inline void add_score_black(const score_t score)
  {
    m_score -= score;
  }

  inline void add_score(const BitBoard white, const BitBoard black, const score_t score)
  {
    m_score += (white.number() - black.number()) * score;
  }

  inline score_t score_white() const
  {
    return m_score;
  }

  inline score_t score(const Color color) const
  {
    return color == Color::White ? m_score : -m_score;
  }

private:
  score_t m_score;
};

const PositionEvaluator::score_t c_passer_score = 80;
// Note that he still gets the normal passer score.
// Note that pawns on the 2nd or 7th rank don't get a bonus here since
// they already get it via piece square table.
const PositionEvaluator::score_t c_36_passer_score = 30;
// Note that 2 connected passers get it 1 time and 3 connected passers get it 2 times.
const PositionEvaluator::score_t c_connected_passer_score = 40;
const PositionEvaluator::score_t c_guarded_passer_score = 30;
const PositionEvaluator::score_t c_isolani_score = -10;
// A pawn that cannot move without being taken by a pawn.
const PositionEvaluator::score_t c_backwards_score = -15;
// A pawn that becomes backward when moved once.
const PositionEvaluator::score_t c_almost_backwards_score = -10;
// Note that n pawns get n-1 times this score.
const PositionEvaluator::score_t c_doubled_score = -20;
// Note that he still gets the normal isolated + doubled scores.
const PositionEvaluator::score_t c_doubled_isolated_score = -30;
// Note that he still gets the normal backward + doubled scores.
// Backwards or almost backwards pawns who have pawns behind them get his malus.
const PositionEvaluator::score_t c_doubled_backwards_score = -10;
// A straggler is a pawn on a halfopen file (when there are still major pieces present)
// which cannot be defended by a pawn. (i.e. isolated or backward or almost backward)
const PositionEvaluator::score_t c_straggler_score = -20;

static PawnTableEntry create_pawn_table_entry(const BitBoard white_pawns, const BitBoard black_pawns)
{
  const BitBoard white_north_fill = white_pawns.north_fill();
  const BitBoard white_south_fill = white_pawns.south_fill();
  const BitBoard white_fill = white_north_fill | white_south_fill;
  const BitBoard black_north_fill = black_pawns.north_fill();
  const BitBoard black_south_fill = black_pawns.south_fill();
  const BitBoard black_fill = black_north_fill | black_south_fill;
  const BitBoard white_front(white_north_fill.one_up());
  const BitBoard black_front(black_south_fill.one_down());
  const BitBoard white_attack_front_east(white_front.one_right());
  const BitBoard white_attack_front_west(white_front.one_left());
  const BitBoard white_attack_front = white_attack_front_east | white_attack_front_west;
  const BitBoard black_attack_front_east(black_front.one_right());
  const BitBoard black_attack_front_west(black_front.one_left());
  const BitBoard black_attack_front = black_attack_front_east | black_attack_front_west;
  const BitBoard white_passers = white_pawns & ~black_front & ~black_attack_front;
  const BitBoard black_passers = black_pawns & ~white_front & ~white_attack_front;
  const BitBoard white_stops = white_pawns.one_up();
  const BitBoard black_stops = black_pawns.one_down();
  const BitBoard white_attacks = white_stops.one_left() | white_stops.one_right();
  const BitBoard black_attacks = black_stops.one_left() | black_stops.one_right();
  const BitBoard white_guarded_passers = white_passers | white_attacks;
  const BitBoard black_guarded_passers = black_passers | black_attacks;
  const BitBoard white_connected_passers(white_passers.one_left() & white_passers);
  const BitBoard black_connected_passers(black_passers.one_left() & black_passers);
  const BitBoard white_neighbor_files(white_fill.one_left() | white_fill.one_right());
  const BitBoard black_neighbor_files(black_fill.one_left() | black_fill.one_right());
  const BitBoard white_isolani = white_pawns & ~white_neighbor_files;
  const BitBoard black_isolani = black_pawns & ~black_neighbor_files;
  const BitBoard white_backward_area = black_attacks & ~white_attack_front & ~white_isolani;
  const BitBoard black_backward_area = white_attacks & ~black_attack_front & ~black_isolani;
  const BitBoard white_backward = (white_stops & white_backward_area).one_down();
  const BitBoard black_backward = (black_stops & black_backward_area).one_up();
  const BitBoard white_almost_backward =
      (white_stops.one_up() & white_backward_area).one_down().one_down()
      | (white_stops.one_up().one_up() & white_backward_area).one_down().one_down().one_down()
      | (white_stops.one_up().one_up().one_up() & white_backward_area).one_down().one_down().one_down().one_down();
  const BitBoard black_almost_backward =
      (black_stops.one_up() & black_backward_area).one_down().one_down()
      | (black_stops.one_up().one_up() & black_backward_area).one_down().one_down().one_down()
      | (black_stops.one_up().one_up().one_up() & black_backward_area).one_down().one_down().one_down().one_down();
  const BitBoard white_doubled = white_front & white_pawns;
  const BitBoard black_doubled = black_front & black_pawns;
  const BitBoard white_doubled_isolated = white_doubled & white_isolani;
  const BitBoard black_doubled_isolated = black_doubled & black_isolani;
  const BitBoard white_doubled_backward = white_doubled & (white_backward | white_almost_backward);
  const BitBoard black_doubled_backward = black_doubled & (black_backward | black_almost_backward);
  const BitBoard white_halfopen_files = ~white_fill & black_fill;
  const BitBoard black_halfopen_files = ~black_fill & white_fill;
  const BitBoard open_files = ~white_fill & ~black_fill;
  const BitBoard white_stragglers = (white_almost_backward | white_backward | white_isolani) & black_halfopen_files;
  const BitBoard black_stragglers = (white_almost_backward | white_backward | white_isolani) & white_halfopen_files;
  const BitBoard behind_passers = white_passers.south_fill().one_down() | black_passers.south_fill().one_up();
  const BitBoard white_trapped_bishops =
      ((black_pawns.one_up().one_left() & black_pawns.one_left().one_left())
      | (black_pawns.one_up().one_right() & black_pawns.one_right().one_right()))
      & c_7_row & (c_a_column | c_h_column);
  const BitBoard black_trapped_bishops =
      ((white_pawns.one_down().one_left() & white_pawns.one_left().one_left())
      | (white_pawns.one_down().one_right() & white_pawns.one_right().one_right()))
      & c_2_row & (c_a_column | c_h_column);
  ScoreCalculator score_calculator;
  score_calculator.add_score(white_passers, black_passers, c_passer_score);
  score_calculator.add_score(white_passers & c_6_row, black_passers & c_3_row, c_36_passer_score);
  score_calculator.add_score(white_connected_passers, black_connected_passers, c_connected_passer_score);
  score_calculator.add_score(white_guarded_passers, black_guarded_passers, c_guarded_passer_score);
  score_calculator.add_score(white_isolani, black_isolani, c_isolani_score);
  score_calculator.add_score(white_backward, black_backward, c_backwards_score);
  score_calculator.add_score(white_almost_backward, black_almost_backward, c_almost_backwards_score);
  score_calculator.add_score(white_doubled, black_doubled, c_doubled_score);
  score_calculator.add_score(white_doubled_isolated, black_doubled_isolated, c_doubled_isolated_score);
  score_calculator.add_score(white_doubled_backward, black_doubled_backward, c_doubled_backwards_score);
  PawnTableEntry entry;
  entry.score = score_calculator.score_white();
  entry.open_files = open_files;
  entry.white_halfopen_files = white_halfopen_files;
  entry.black_halfopen_files = black_halfopen_files;
  entry.major_piece_score_white = white_stragglers.number() * c_straggler_score;
  entry.major_piece_score_black = black_stragglers.number() * c_straggler_score;
  entry.behind_passers = behind_passers;
  entry.white_trapped_bishops = white_trapped_bishops;
  entry.black_trapped_bishops = black_trapped_bishops;
  return entry;
}

const PositionEvaluator::score_t c_halfopen_rook_score = 10;
const PositionEvaluator::score_t c_open_rook_score = 15;
const PositionEvaluator::score_t c_behind_passer_rook_score = 20;
const PositionEvaluator::score_t c_trapped_bishop_score = -150;

static PositionEvaluator::score_t adjust_score(const ChessBoard& board,
                                               const PawnTableEntry& entry)
{
  ScoreCalculator score_calculator(entry.score);
  const BitBoard white_rooks = board.rook_board(Color::White);
  const BitBoard black_rooks = board.rook_board(Color::Black);
  const BitBoard white_bishops = board.bishop_board(Color::White);
  const BitBoard black_bishops = board.bishop_board(Color::Black);
  const BitBoard white_halfopen_rooks = white_rooks & entry.white_halfopen_files;
  const BitBoard black_halfopen_rooks = black_rooks & entry.black_halfopen_files;
  const BitBoard white_open_rooks = white_rooks & entry.white_halfopen_files;
  const BitBoard black_open_rooks = black_rooks & entry.black_halfopen_files;
  const BitBoard white_behind_passer_rooks = white_rooks & entry.behind_passers;
  const BitBoard black_behind_passer_rooks = black_rooks & entry.behind_passers;
  const BitBoard white_trapped_bishops = white_bishops & entry.white_trapped_bishops;
  const BitBoard black_trapped_bishops = black_bishops & entry.black_trapped_bishops;
  score_calculator.add_score(white_halfopen_rooks, black_halfopen_rooks, c_halfopen_rook_score);
  score_calculator.add_score(white_open_rooks, black_open_rooks, c_open_rook_score);
  if (board.rook_board(Color::Black) | board.queen_board(Color::Black)) {
    score_calculator.add_score_white(entry.major_piece_score_white);
  }
  if (board.rook_board(Color::White) | board.queen_board(Color::White)) {
    score_calculator.add_score_black(entry.major_piece_score_black);
  }
  score_calculator.add_score(white_behind_passer_rooks, black_behind_passer_rooks, c_behind_passer_rook_score);
  score_calculator.add_score(white_trapped_bishops, black_trapped_bishops, c_trapped_bishop_score);
  return score_calculator.score(board.turn_color());
}

PositionEvaluator::score_t PawnEvaluator::evaluate(SearchState* const /* state */,
                                                   SearchContext* const context)
{
  const PawnTableEntry* const entry = context->get_pawns();
  if (entry) {
    return adjust_score(context->board, *entry);
  }
  const BitBoard white_pawns = context->board.pawn_board(Color::White);
  const BitBoard black_pawns = context->board.pawn_board(Color::Black);
  PawnTableEntry new_entry = create_pawn_table_entry(white_pawns, black_pawns);
  context->put_pawns(new_entry);
  return adjust_score(context->board, new_entry);
}

} // namespace olaf

