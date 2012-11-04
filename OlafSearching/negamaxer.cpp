#include "negamaxer.h"
#include "OlafRules/move.h"
#include <limits>
#include <future>

using namespace std;

NegaMaxer::NegaMaxer(const std::shared_ptr<MoveGenerator> &generator, const std::shared_ptr<MoveOrderer> &orderer, const std::shared_ptr<AlphaBetaSearcher> &searcher, bool ignore_depth):
  m_generator (generator),
  m_orderer (orderer),
  m_searcher (searcher),
  m_ignore_depth (ignore_depth)
{}

SearchResult NegaMaxer::search_alpha_beta(ChessBoard &board, int depth, int nodes_searched, int alpha, int beta, const std::shared_ptr<Stopper> &stopper)
{
  if ((!m_ignore_depth && depth <= 0) || board.finished()) {
    return m_searcher->search_stoppable_alpha_beta(board, depth, nodes_searched, alpha, beta, stopper);
  }
  vector<Move> moves = m_generator->generate_moves(board);
  if (moves.empty()) {
    return m_searcher->search_stoppable_alpha_beta(board, depth, nodes_searched, alpha, beta, stopper);
  }
  m_orderer->order_moves(board, moves);
  vector<Move> alpha_variation;
  int nodes = 0;
  for (Move &move : moves) {
    move.execute(board);
    SearchResult result = search_stoppable_alpha_beta(board, depth - 1, nodes_searched + nodes, -beta, -alpha, stopper);
    int value = -result.value();
    move.undo(board);
    nodes += result.nodes();
    if (value >= beta) {
      return SearchResult(nodes, value, result.main_variation());
    } else if (value > alpha) {
      alpha = value;
      alpha_variation = result.main_variation();
      alpha_variation.push_back(move);
    }
  }
  return SearchResult(nodes, alpha, alpha_variation);
}
