#include "olaf/evaluation/pawnevaluator.h"

#include "olaf/transposition_table/pawntable.h"

using namespace std;

namespace olaf
{

const PositionEvaluator::score_t c_passer_score = 100;
// Note that he still gets the normal passer score.
// Note that pawns on the 2nd or 7th rank don't get a bonus here since
// they already get it via piece square table.
const PositionEvaluator::score_t c_36_passer_score = 200;
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

class ScoreCalculator {
public:
  typedef PositionEvaluator::score_t score_t;
  inline void add_score(const BitBoard white, const BitBoard black, const score_t score)
  {
    m_score += (white.number() - black.number()) * score;
  }

  inline void passers(const BitBoard white, const BitBoard black)
  {
    add_score(white, black, c_passer_score);
  }

  inline void rank_36_passers(const BitBoard white, const BitBoard black)
  {
    add_score(white, black, c_36_passer_score);
  }

  inline void isolani(const BitBoard white, const BitBoard black)
  {
    add_score(white, black, c_isolani_score);
  }

  inline void backward(const BitBoard white, const BitBoard black)
  {
    add_score(white, black, c_backwards_score);
  }

  inline void almost_backward(const BitBoard white, const BitBoard black)
  {
    add_score(white, black, c_almost_backwards_score);
  }

  inline void doubled(const BitBoard white, const BitBoard black)
  {
    add_score(white, black, c_doubled_score);
  }

  inline void doubled_isolated(const BitBoard white, const BitBoard black)
  {
    add_score(white, black, c_doubled_isolated_score);
  }

  inline void doubled_backward(const BitBoard white, const BitBoard black)
  {
    add_score(white, black, c_doubled_backwards_score);
  }

  inline score_t score(const Color color)
  {
    return color == Color::White ? m_score : -m_score;
  }

private:
  score_t m_score = 0;
};

PositionEvaluator::score_t PawnEvaluator::evaluate(SearchState* const /* state */,
                                                   SearchContext* const context)
{
  {
    const PawnTableEntry* const entry = context->get_pawns();
    if (entry) {
      return entry->score;
    }
  }
  const BitBoard white_pawns = context->board.pawn_board(Color::White);
  const BitBoard black_pawns = context->board.pawn_board(Color::Black);
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
  const BitBoard white_neighbors(white_fill.one_left() | white_fill.one_right());
  const BitBoard white_isolani = white_pawns & ~white_neighbors;
  const BitBoard black_neighbors(black_fill.one_left() | black_fill.one_right());
  const BitBoard black_isolani = black_pawns & ~black_neighbors;
  const BitBoard white_stops = white_pawns.one_up();
  const BitBoard black_stops = black_pawns.one_down();
  const BitBoard white_attacks = white_stops.one_left() | white_stops.one_right();
  const BitBoard black_attacks = black_stops.one_left() | black_stops.one_right();
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
  ScoreCalculator score_calculator;
  score_calculator.passers(white_passers, black_passers);
  score_calculator.rank_36_passers(white_passers & c_6_row, black_passers & c_3_row);
  score_calculator.isolani(white_isolani, black_isolani);
  score_calculator.backward(white_backward, black_backward);
  score_calculator.almost_backward(white_almost_backward, black_almost_backward);
  score_calculator.doubled(white_doubled, black_doubled);
  score_calculator.doubled_isolated(white_doubled_isolated, black_doubled_isolated);
  score_calculator.doubled_backward(white_doubled_backward, black_doubled_backward);
  const score_t score = score_calculator.score(context->board.turn_color());
  {
    PawnTableEntry entry;
    entry.score = score;
    context->put_pawns(entry);
  }
  return score;
}

} // namespace olaf

