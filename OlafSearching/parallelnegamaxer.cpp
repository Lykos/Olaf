#include "parallelnegamaxer.h"
#include "OlafRules/move.h"
#include <limits>
#include <future>

using namespace std;

ParallelNegaMaxer::ParallelNegaMaxer(const shared_ptr<MoveGenerator> &generator, const shared_ptr<MoveOrderer> &orderer, const shared_ptr<AlphaBetaSearcher> &searcher, int sequential_depth):
  m_generator (generator),
  m_orderer (orderer),
  m_searcher (searcher),
  m_sequential_depth (sequential_depth)
{}


static SearchResult eval_move(ParallelNegaMaxer *nega_maxer, Move move, ChessBoard board, int depth, int nodes_searched, int alpha, int beta, const shared_ptr<Stopper> &stopper)
{
  move.execute(board);
  SearchResult result = nega_maxer->search_stoppable_alpha_beta(board, depth, nodes_searched, -beta, -alpha, stopper);
  result.add_move(move);
  return result;
}

SearchResult ParallelNegaMaxer::search_alpha_beta(ChessBoard &board, int depth, int nodes_searched, int alpha, int beta, const shared_ptr<Stopper> &stopper)
{
  if (depth <= m_sequential_depth || board.finished()) {
    return m_searcher->search_stoppable_alpha_beta(board, depth, nodes_searched, alpha, beta, stopper);
  }
  vector<Move> moves = m_generator->generate_moves(board);
  if (moves.empty()) {
    return m_searcher->search_stoppable_alpha_beta(board, depth, nodes_searched, alpha, beta, stopper);
  }
  m_orderer->order_moves(board, moves);
  vector<Move> alpha_variation;
  auto it = moves.begin();
  // Do the first one synchronously
  SearchResult first_result = eval_move(this, *it, board, depth, nodes_searched, alpha, beta, stopper);
  ++it;
  int value = -first_result.value();
  unsigned int nodes = first_result.nodes();
  if (value >= beta) {
    return first_result;
  } else if (value > alpha) {
    alpha = value;
    alpha_variation = first_result.main_variation();
  }
  vector< future<SearchResult> > other_results;
  for (; it < moves.end(); ++it) {
    other_results.push_back(async(launch::async, eval_move, this, *it, board, depth, nodes_searched + nodes, alpha, beta, stopper));
  }
  for (future<SearchResult> &fut : other_results) {
    fut.wait();
    SearchResult result = fut.get();
    nodes += result.nodes();
    int value = -result.value();
    if (value >= beta) {
      return SearchResult(nodes, value, result.main_variation());
    } else if (value > alpha) {
      alpha = value;
      alpha_variation = result.main_variation();
    }
  }
  return SearchResult(nodes, alpha, alpha_variation);
}
