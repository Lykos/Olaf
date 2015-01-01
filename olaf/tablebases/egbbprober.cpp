#include "olaf/tablebases/egbbprober.h"

#include <cassert>
#include <sstream>
#include <dlfcn.h>
#include <gflags/gflags.h>

#include "olaf/status.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/movechecker.h"
#include "olaf/evaluation/positionevaluator.h"

DEFINE_string(egbb_shared_library, "libegbbso.so", "Name of the shared library for egbb probing.");

using namespace std;

namespace olaf
{

// Copied from the egbb library header
enum {
  _WHITE,
  _BLACK
};

enum {
  _EMPTY,
  _WKING,
  _WQUEEN,
  _WROOK,
  _WBISHOP,
  _WKNIGHT,
  _WPAWN,
  _BKING,
  _BQUEEN,
  _BROOK,
  _BBISHOP,
  _BKNIGHT,
  _BPAWN
};

enum {
  LOAD_NONE,
  LOAD_4MEN,
  SMART_LOAD,
  LOAD_5MEN,
  LOAD_5MEN_LZ
};

const int c_not_found = 99999;

const char c_load_egbb_xmen[] = "load_egbb_xmen";

const char c_probe_egbb_xmen[] = "probe_egbb_xmen";

const int c_min_cache_size = 8216;

static void delete_shared_library(void* handle)
{
  if (handle) {
    dlclose(handle);
  }
}

EgbbProber::EgbbProber(const long cache_size):
  m_lib_handle(nullptr),
  m_probe_egbb(nullptr),
  m_load_egbb(nullptr),
  m_cache_size(cache_size)
{}

Status EgbbProber::load(const string& egbb_path)
{
  if (m_cache_size < c_min_cache_size) {
    ostringstream oss;
    oss << "The cache size has to be at least " << c_min_cache_size;
    return Status::error(oss.str());
  }
  if (!m_lib_handle) {
    m_lib_handle.reset(dlopen(FLAGS_egbb_shared_library.c_str(), RTLD_LAZY), delete_shared_library);
    if (!m_lib_handle) {
      ostringstream oss;
      oss << "Could not load shared library " << FLAGS_egbb_shared_library;
      const char* error = dlerror();
      if (error) {
        oss << ": " << error;
      }
      return Status::error(oss.str());
    }
  }
  if (!m_load_egbb) {
    m_load_egbb = load_egbb_t(long(dlsym(m_lib_handle.get(), c_load_egbb_xmen)));
    if (!m_load_egbb) {
      ostringstream oss;
      oss << "Could not find symbol " << c_load_egbb_xmen << " in shared library " << FLAGS_egbb_shared_library;
      const char* error = dlerror();
      if (error) {
        oss << ": " << error;
      }
      return Status::error(oss.str());
    }
  }
  if (!m_probe_egbb) {
    m_probe_egbb = probe_egbb_t(long(dlsym(m_lib_handle.get(), c_probe_egbb_xmen)));
    if (!m_probe_egbb) {
      ostringstream oss;
      oss << "Could not find symbol " << c_probe_egbb_xmen << " in shared library " << FLAGS_egbb_shared_library;
      const char* const error = dlerror();
      if (error) {
        oss << ": " << error;
      }
      return Status::error(oss.str());
    }
  }
  m_load_egbb(egbb_path.c_str(), m_cache_size, SMART_LOAD);
  return Status::valid();
}

static const int c_max_pieces = 6;

bool EgbbProber::probe(const ChessBoard& board, score_t* const score)
{
  if (board.occupied().number() > c_max_pieces || m_probe_egbb == nullptr || board.finished()) {
    return false;
  }
  if (MoveChecker::can_kill_king(board)) {
    return PositionEvaluator::c_win_score;
  }
  int pieces[c_max_pieces + 1];
  int squares[c_max_pieces + 1];
  int count = 0;
#define ADD_PIECE(piece_board, type) \
  { \
    BitBoard bit_board = piece_board; \
    while (bit_board) { \
      pieces[count] = type; \
      squares[count] = bit_board.next_position().index(); \
      ++count; \
    } \
  }

  ADD_PIECE(board.rook_board(Color::White), _WROOK);
  ADD_PIECE(board.knight_board(Color::White), _WKNIGHT);
  ADD_PIECE(board.bishop_board(Color::White), _WBISHOP);
  ADD_PIECE(board.queen_board(Color::White), _WQUEEN);
  ADD_PIECE(board.king_board(Color::White), _WKING);
  ADD_PIECE(board.pawn_board(Color::White), _WPAWN);

  ADD_PIECE(board.rook_board(Color::Black), _BROOK);
  ADD_PIECE(board.knight_board(Color::Black), _BKNIGHT);
  ADD_PIECE(board.bishop_board(Color::Black), _BBISHOP);
  ADD_PIECE(board.queen_board(Color::Black), _BQUEEN);
  ADD_PIECE(board.king_board(Color::Black), _BKING);
  ADD_PIECE(board.pawn_board(Color::Black), _BPAWN);
#undef ADD_PIECE
  pieces[count] = _EMPTY;
  squares[count] = board.ep_captures().first_position().index();
  const int player = board.turn_color() == Color::White ? _WHITE : _BLACK;
  const int found_score = m_probe_egbb(player, pieces, squares);
  if (found_score == c_not_found) {
    return false;
  }
  *score = found_score;
  return true;
}
} // namespace olaf
