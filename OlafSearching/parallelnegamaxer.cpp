#include "parallelnegamaxer.h"
#include "OlafRules/move.h"
#include <limits>
#include <future>

using namespace std;

ParallelNegaMaxer::ParallelNegaMaxer(unique_ptr<MoveGenerator> generator,
                                     unique_ptr<MoveOrderer> orderer,
                                     unique_ptr<AlphaBetaSearcher> searcher,
                                     const int sequential_depth):
  m_generator(move(generator)),
  m_orderer(move(orderer)),
  m_searcher(move(searcher)),
  m_sequential_depth(sequential_depth)
{}


static SearchResult eval_move(ParallelNegaMaxer *nega_maxer,
                              const ChessBoard& board,
                              const int depth,
                              const int nodes_searched,
                              const int alpha,
                              const int beta,
                              const Stopper* const stopper,
                              Move* const move)
{
  ChessBoard board_copy(board);
  move->execute(&board_copy);
  SearchResult result =
      nega_maxer->search_stoppable_alpha_beta(&board_copy,
                                              depth - 1,
                                              nodes_searched,
                                              -beta,
                                              -alpha,
                                              *stopper);
  result.add_move(*move);
  return result;
}

SearchResult ParallelNegaMaxer::search_alpha_beta(ChessBoard* const board,
                                                  const int depth,
                                                  const int nodes_searched,
                                                  int alpha,
                                                  const int beta,
                                                  const Stopper& stopper)
{
  if (depth <= m_sequential_depth || board->finished()) {
    return m_searcher->search_stoppable_alpha_beta(board, depth, nodes_searched, alpha, beta, stopper);
  }
  vector<Move> moves = m_generator->generate_moves(*board);
  if (moves.empty()) {
    return m_searcher->search_stoppable_alpha_beta(board, depth, nodes_searched, alpha, beta, stopper);
  }
  m_orderer->order_moves(*board, &moves);
  vector<Move> alpha_variation;
  auto it = moves.begin();
  // Do the first one synchronously
  Move* const move = &(*it);
  SearchResult first_result = eval_move(this, *board, depth, nodes_searched, alpha, beta, &stopper, move);
  if (!first_result.valid()) {
    return first_result;
  }
  ++it;
  int value = -first_result.value();
  unsigned int nodes = first_result.nodes();
  if (value >= beta) {
    return first_result;
  } else if (value > alpha) {
    alpha = value;
    alpha_variation.clear();
    for (const Move& move : first_result.main_variation()) {
      alpha_variation.push_back(move);
    }
  }
  vector<future<SearchResult>> other_results;
  for (; it < moves.end(); ++it) {
    Move* const move = &(*it);
    other_results.push_back(async(launch::async, eval_move, this, *board, depth, nodes_searched + nodes, alpha, beta, &stopper, move));
  }
  bool valid = true;
  for (future<SearchResult> &fut : other_results) {
    fut.wait();
    SearchResult result = fut.get();
    valid &= result.valid();
    nodes += result.nodes();
    int value = -result.value();
    if (value >= beta) {
      return SearchResult(nodes, value, result.main_variation());
    } else if (value > alpha) {
      alpha = value;
      alpha_variation.clear();
      for (const Move& move : result.main_variation()) {
        alpha_variation.push_back(move);
      }
    }
  }
  if (!valid) {
    return SearchResult();
  }
  return SearchResult(nodes, alpha, alpha_variation);
}
