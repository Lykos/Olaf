#ifndef EGBBPROBER_H
#define EGBBPROBER_H

#include <string>
#include "olaf/status.h"

namespace olaf
{

class ChessBoard;

extern "C" typedef int (*probe_egbb_t) (int player, int* piece, int* square);

extern "C" typedef void (*load_egbb_t) (const char* path, int cache_size, int load_options);

class EgbbProber
{
public:
  explicit EgbbProber(long cache_size);

  ~EgbbProber();

  Status load_egbb(const std::string& egbb_path);

  bool probe(const ChessBoard& board, int* score) const;

  void cache_size(long cache_size);
private:
  void* m_lib_handle;

  probe_egbb_t m_probe_egbb;

  load_egbb_t m_load_egbb;

  long m_cache_size;
};

} // namespace olaf

#endif // EGBBPROBER_H
