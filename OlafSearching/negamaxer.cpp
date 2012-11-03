#include "negamaxer.h"
#include "move.h"
#include <limits>
#include <future>

using namespace boost;
using namespace std;

NegaMaxer::NegaMaxer(shared_ptr<PositionEvaluator> evaluator, shared_ptr<MoveOrderer> orderer):
  m_evaluator (evaluator),
  m_orderer (orderer)
{}

SearchResult NegaMaxer::no_parallel_search(ChessBoard &board, int depth, int alpha, int beta)
{
  if (should_stop()) {
    return SearchResult();
  } else if (depth <= 0) {
    return SearchResult(1, m_evaluator->evaluate(board));
  }
  vector<Move> moves = m_generator.generate_moves(board);
  m_orderer->order_moves(board, moves);
  vector<Move> alpha_variation;
  unsigned int nodes = 0;
  for (Move &move : moves) {
    move.execute(board);
    SearchResult result = -no_parallel_search(board, depth - 1, -beta, -alpha);
    move.undo(board);
    nodes += result.nodes;
    if (result.value >= beta) {
      return SearchResult(nodes, result.value, result.main_variation());
    } else if (result.value > alpha) {
      alpha = result.value;
      alpha_variation = result.main_variation();
    }
  }
  return SearchResult(nodes, alpha, alpha_variation);
}

static NegaMaxerInternalSearchResult async_eval(NegaMaxer &nega_maxer, const Move& move, ChessBoard board, int depth, int alpha, int beta)
{
  move.execute(board);
  SearchResult result = nega_maxer.internal_search(board, depth, -beta, -alpha);
  return result;
}

SearchResult NegaMaxer::search_alpha_beta(ChessBoard &board, int depth, int alpha, int beta)
{
  if (should_stop()) {
    return SearchResult();
  } else if (depth <= 0) {
    return SearchResult(1, m_evaluator->evaluate(board));
  } else if (depth <= no_parallel_depth) {
    return no_parallel_search(board, depth, alpha, beta);
  }
  vector<Move> moves = m_generator->generate_moves(board);
  m_orderer->order_moves(board, moves);
  vector<Move> alpha_variation;
  auto it = moves.begin();
  // TODO: No moves
  // Do the first one synchronously
  it->execute(board);
  SearchResult first_result = -internal_search(board, depth - 1, -beta, -alpha);
  it->undo(board);
  first_result.add_move(*it);
  ++it;
  unsigned int nodes = first_result.nodes;
  if (first_result.value >= beta) {
    return first_result;
  } else if (first_result.value > alpha) {
    alpha = first_result.value;
    alpha_variation = first_result.main_variation();
  }
  vector<future<NegaMaxerInternalSearchResult>> other_results;
  for (; it < moves.end(); ++it) {
    other_results.push(async(launch::async, async_eval, (*this, *it, board, depth, alpha, beta)));
  }
  for (future<NegaMaxerInternalSearchResult> &fut : other_results) {
    fut.wait();
    SearchResult result = fut.get();
    nodes += result.nodes;
    if (result.value >= beta) {
      return SearchResult(nodes, result.value, result.main_variation());
    } else if (result.value > alpha) {
      alpha = result.value;
      alpha_variation = result.main_variation();
    }
  }
  return SearchResult(nodes, alpha, alpha_variation);
}
