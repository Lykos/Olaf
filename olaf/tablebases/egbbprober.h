#ifndef EGBBPROBER_H
#define EGBBPROBER_H

#include <memory>
#include <string>

#include "olaf/status.h"
#include "olaf/tablebases/tablebaseprober.h"

namespace olaf
{

class ChessBoard;

extern "C" typedef int (*probe_egbb_t) (int player, int* piece, int* square);

extern "C" typedef void (*load_egbb_t) (const char* path, int cache_size, int load_options);

class EgbbProber : public TablebaseProber
{
public:
  explicit EgbbProber(long cache_size);

  Status load(const std::string& egbb_path);

  bool probe(const ChessBoard& board, score_t* score) override;

  inline bool is_initialized() const { return m_probe_egbb; }

private:
  std::shared_ptr<void> m_lib_handle;

  probe_egbb_t m_probe_egbb;

  load_egbb_t m_load_egbb;

  const long m_cache_size;
};

} // namespace olaf

#endif // EGBBPROBER_H
