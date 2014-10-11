#include "negamaxer.h"
#include "OlafRules/move.h"
#include <limits>
#include <future>

using namespace std;

NegaMaxer::NegaMaxer(std::unique_ptr<MoveGenerator> generator,
                     std::unique_ptr<MoveOrderer> orderer,
                     std::unique_ptr<AlphaBetaSearcher> searcher,
                     const bool ignore_depth):
  m_generator(move(generator)),
  m_orderer(move(orderer)),
  m_searcher(move(searcher)),
  m_ignore_depth(ignore_depth)
{}

SearchResult NegaMaxer::search_alpha_beta(ChessBoard* const board,
                                          const int depth,
                                          const int nodes_searched,
                                          int alpha,
                                          const int beta,
                                          const Stopper& stopper)
{
  if ((!m_ignore_depth && depth <= 0) || board->finished()) {
    return m_searcher->search_stoppable_alpha_beta(board, depth, nodes_searched, alpha, beta, stopper);
  }
  vector<Move> moves = m_generator->generate_moves(*board);
  if (moves.empty()) {
    return m_searcher->search_stoppable_alpha_beta(board, depth, nodes_searched, alpha, beta, stopper);
  }
  m_orderer->order_moves(*board, &moves);
  vector<Move> alpha_variation;
  int nodes = 0;
  for (Move& move : moves) {
    move.execute(board);
    SearchResult result = search_stoppable_alpha_beta(board,
                                                      depth - 1,
                                                      nodes_searched + nodes,
                                                      -beta,
                                                      -alpha,
                                                      stopper);
    if (!result.valid()) {
      return result;
    }
    int value = -result.value();
    move.undo(board);
    nodes += result.nodes();
    if (value >= beta) {
      return SearchResult(nodes, value, result.main_variation());
    } else if (value > alpha) {
      alpha = value;
      alpha_variation.clear();
      for (const Move& move : result.main_variation()) {
        alpha_variation.push_back(move);
      }
      alpha_variation.push_back(move);
    }
  }
  return SearchResult(nodes, alpha, alpha_variation);
}
