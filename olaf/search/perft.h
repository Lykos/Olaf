#ifndef PERFT_H
#define PERFT_H

#include <memory>
#include <string>
#include <ostream>
#include <vector>

namespace olaf
{

class MoveGenerator;
class ChessBoard;
class Move;

/**
 * @brief The Perft class is used to calculate statistics about how many moves of which type there
 *        are at which depth. This is only used for testing, debugging and benchmarking. The reason
 *        it resides here and not in the test is that it can be used in both the benchmarks and the
 *        tests.
 */
class Perft
{
public:
  typedef unsigned long long u64;

  struct PerftResult {
    u64 nodes;
    u64 captures;
    u64 ep;
    u64 castles;
    u64 promotions;
    u64 mates;

    PerftResult& operator +=(const PerftResult& right);
  };

  struct PerftExample {
    const std::string name;
    const std::string fen;
    const std::vector<PerftResult> expected_results;
  };

  static const std::vector<PerftExample>& examples();

  /**
   * @brief Perft takes ownership of both arguments.
   */
  explicit Perft(std::unique_ptr<MoveGenerator> generator);

  PerftResult perft(const int depth,
                    const ChessBoard& board);

  void debug_perft(const int depth,
                   const ChessBoard& board);

private:
  PerftResult internal_perft(const int depth,
                             ChessBoard* const board);

  std::unique_ptr<MoveGenerator> m_generator;
};

bool operator ==(const Perft::PerftResult& right, const Perft::PerftResult& left);

std::ostream& operator <<(std::ostream& out, const Perft::PerftResult& perft_result);

} // namespace olaf

#endif // PERFT_H
