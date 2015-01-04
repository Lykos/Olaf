#include "olaf/search/searcherfactory.h"

#include "olaf/search/simpletimedsearcher.h"
#include "olaf/search/iterativedeepener.h"
#include "olaf/search/negamaxer.h"
#include "olaf/search/capturegenerator.h"
#include "olaf/search/simplemovegenerator.h"
#include "olaf/search/moveorderer.h"
#include "olaf/search/quiescer.h"
#include "olaf/search/perft.h"
#include "olaf/search/openingbooksearcher.h"
#include "olaf/evaluation/positionevaluator.h"
#include "olaf/parse/sanparser.h"
#include "olaf/parse/epdparser.h"
#include "olaf/transposition_table/transpositiontable.h"
#include "olaf/config.h"

using namespace std;
using namespace chrono;

namespace olaf
{

// static
unique_ptr<MoveGenerator> SearcherFactory::capture_generator()
{
  unique_ptr<MoveGenerator> generator(new CaptureGenerator(move_generator()));
  return generator;
}

// static
unique_ptr<MoveGenerator> SearcherFactory::move_generator()
{
  unique_ptr<MoveGenerator> generator(new SimpleMoveGenerator);
  return generator;
}

// static
unique_ptr<Perft> SearcherFactory::perft()
{
  unique_ptr<Perft> perft(new Perft(move_generator()));
  return perft;
}

// static
unique_ptr<SanParser> SearcherFactory::san_parser()
{
  unique_ptr<SanParser> parser(new SanParser(move_generator()));
  return parser;
}

// static
unique_ptr<EpdParser> SearcherFactory::epd_parser()
{
  unique_ptr<EpdParser> parser(new EpdParser(san_parser()));
  return parser;
}

SearcherFactory::SearcherFactory(ThinkingWriter* const writer,
                                 const Config* const config):
  m_writer(writer),
  m_evaluator_factory(&(config->evaluation)),
  m_config(config)
{}

unique_ptr<Searcher> SearcherFactory::searcher() const
{
  return opening_book_searcher();
}

unique_ptr<Searcher> SearcherFactory::opening_book_searcher() const
{
  unique_ptr<Searcher> searcher(new OpeningBookSearcher(timed_searcher()));
  return searcher;
}

unique_ptr<Searcher> SearcherFactory::timed_searcher() const
{
  unique_ptr<Searcher> searcher(new SimpleTimedSearcher(
                                  iterative_searcher(),
                                  m_config->search.default_moves_to_play));
  return searcher;
}

unique_ptr<Searcher> SearcherFactory::iterative_searcher() const
{
  unique_ptr<Searcher> searcher(new IterativeDeepener(
                                  sequential_alpha_beta_searcher(),
                                  m_writer,
                                  m_config->search.min_depth,
                                  m_config->search.initial_window));
  return searcher;
}

unique_ptr<AlphaBetaSearcher> SearcherFactory::sequential_alpha_beta_searcher() const
{
  assert(m_config->search.use_quiescent_search);
  unique_ptr<AlphaBetaSearcher> sub_searcher =
      m_config->search.use_quiescent_search ? quiescer() : evaluator();
  unique_ptr<AlphaBetaSearcher> searcher(new NegaMaxer(move_generator(),
                                                       move_orderer(),
                                                       move(sub_searcher),
                                                       0,
                                                       false));
  return searcher;
}

unique_ptr<AlphaBetaSearcher> SearcherFactory::quiescer() const
{
  unique_ptr<AlphaBetaSearcher> searcher(new Quiescer(evaluator(),
                                                      capture_generator(),
                                                      move_orderer(),
                                                      evaluator(),
                                                      0,
                                                      true));
  return searcher;
}

unique_ptr<PositionEvaluator> SearcherFactory::evaluator() const
{
  return m_evaluator_factory.evaluator();
}

unique_ptr<TranspositionTable> SearcherFactory::transposition_table() const
{
  unique_ptr<TranspositionTable> table;
  const long size = m_config->transposition_table.size;
  if (size) {
    table.reset(new TranspositionTable(size));
  }
  return table;
}


unique_ptr<PawnTable> SearcherFactory::pawn_table() const
{
  unique_ptr<PawnTable> table;
  const long size = m_config->transposition_table.pawn_size;
  if (size) {
    table.reset(new PawnTable(size));
  }
  return table;
}

unique_ptr<EgbbProber> SearcherFactory::egbb_prober() const
{
  unique_ptr<EgbbProber> prob(new EgbbProber(m_config->tablebases.cache_size));
  return prob;
}

MoveOrderer SearcherFactory::move_orderer() const
{
  return MoveOrderer(m_config->move_ordering);
}

} // namespace olaf
