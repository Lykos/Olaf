#include "negamaxer.h"
#include "move.h"
#include <limits>
#include <future>

using namespace std;

NegaMaxer::NegaMaxer(std::unique_ptr<MoveGenerator> generator,
                     std::unique_ptr<MoveOrderer> orderer,
                     std::unique_ptr<AlphaBetaSearcher> sub_searcher,
                     const int sub_searcher_depth,
                     const bool ignore_depth):
  AlphaBetaSearcher(move(sub_searcher), sub_searcher_depth, ignore_depth),
  m_generator(move(generator)),
  m_orderer(move(orderer))
{}

SearchResult NegaMaxer::alpha_beta(SearchState* const state,
                                   SearchContext* const context)
{
  vector<Move> moves = m_generator->generate_moves(context->board);
  if (moves.empty()) {
    return recurse_sub_searcher(*state, context);
  }
  m_orderer->order_moves(context->board, &moves);
  SearchResult result;
  for (Move& move : moves) {
    SearchResult current_result = recurse_move(*state, context, &move);
    switch (update_result(move, &current_result, state, &result)) {
      case ResultReaction::INVALID:
        return SearchResult::invalid();
      case ResultReaction::RETURN:
        return result;
      case ResultReaction::CONTINUE:
        break;
    }
  }
  return result;
}
