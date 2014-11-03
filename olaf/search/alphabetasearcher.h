#ifndef ALPHABETASEARCHER_H
#define ALPHABETASEARCHER_H

#include <memory>
#include <vector>

#include "olaf/search/searcher.h"
#include "olaf/rules/move.h"
#include "olaf/search/moveorderer.h"
#include "olaf/search/searchresult.h"
#include "olaf/search/searchstate.h"

namespace olaf
{

class SearchContext;
class MoveGenerator;

/**
 * @brief The RecursiveSearcher class is an abstract searcher which provides
 *        the method recursive_search which can be called by subclasses.
 *        It stops, if required, otherwise, it calls recursive_search which should
 *        be implemented by its subclasses.
 */
class AlphaBetaSearcher : public Searcher
{
public:
  AlphaBetaSearcher();

  AlphaBetaSearcher(std::unique_ptr<MoveGenerator> generator,
                    const MoveOrderer& orderer,
                    std::unique_ptr<AlphaBetaSearcher> sub_searcher,
                    depth_t sub_searcher_depth,
                    bool ignore_depth);

  virtual ~AlphaBetaSearcher();

  /**
   * @brief search is the entry point which sets up the initial search state and starts the search.
   */
  SearchResult search(SearchContext* context) final;

  SearchResult search_windowed(SearchContext* context, score_t alpha, score_t beta);

  /**
   * @brief recurse_alpha_beta should be called internally to recurse to the sub searcher.
   * @param current_state the SearchState of the calling method.
   * @param context the global SearchContext.
   */
  SearchResult recurse_sub_searcher(const SearchState& current_state,
                                    SearchContext* context);

  /**
   * @brief recurse_alpha_beta should be called internally to recurse. It takes care of
   *        stoppers, creates a new SearchState and calls alpha_beta.
   * @param current_state the SearchState of the calling method.
   * @param context the global SearchContext.
   */
  SearchResult recurse_alpha_beta(const SearchState& current_state,
                                  SearchContext* context);

  /**
   * @brief search_move shortcut for executing a move, recursing and not undoing.
   */
  SearchResult recurse_move_noundo(Move move,
                                   const SearchState& current_state,
                                   SearchContext* context);

  /**
   * @brief search_move shortcut for executing a move, recursing and undoing.
   */
  SearchResult recurse_move(Move move,
                            const SearchState& current_state,
                            SearchContext* context);

protected:
  std::vector<Move> generate_ordered_moves(const SearchContext& context, const SearchState& state);

  /**
   * @brief The ResultReaction enum tells the searcher what to do after update_result has returned.
   */
  enum class ResultReaction {
    CONTINUE,
    INVALID,
    RETURN
  };

  /**
   * @brief update_result updates the result for the current method based on the
   *        result from a recursive call. The return value decides how to proceed.
   * @param move the move that was executed. The object is consumed.
   * @param recursive_result is the result gotten from a recursive call.
   * @param context the global context of the search.
   * @param state the current state of the search.
   * @param result the result of the current method.
   * @return INVALID if the search should be stopped and an invalid result should be returned.
   *         CONTINUE if the search should continue as normal.
   *         RETURN if the result should be returned now.
   */
  ResultReaction update_result(Move move,
                               SearchResult* recursive_result,
                               SearchContext* const context,
                               SearchState* state,
                               SearchResult* result) const;

  /**
   * @brief alpha_beta should be implemented by subclasses to do the search. For recursion,
   *        alpha_beta should not be called directly. Instead, search_move or recurse_alpha_beta
   *        should be used.
   */
  virtual SearchResult alpha_beta(SearchState* state, SearchContext* context) = 0;

private:
  std::unique_ptr<MoveGenerator> m_generator;

  MoveOrderer m_orderer;

  std::unique_ptr<AlphaBetaSearcher> m_sub_searcher;

  const int m_sub_searcher_depth;

  const bool m_ignore_depth;

};

} // namespace olaf

#endif // ALPHABETASEARCHER_H
