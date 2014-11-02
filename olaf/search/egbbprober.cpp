#include "olaf/search/egbbprober.h"

#include <cassert>
#include <sstream>
#include <dlfcn.h>
#include <gflags/gflags.h>

#include "olaf/status.h"
#include "olaf/rules/chessboard.h"

DEFINE_string(egbb_shared_library, "egbbso", "Name of the shared library for egbb probing.");

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

extern "C" typedef void (*load_egbb_t) (const char* path, int cache_size, int load_options);

const char c_load_egbb_xmen[] = "load_egbb_xmen";

const char c_probe_egbb_xmen[] = "load_probe_xmen";

EgbbProber::EgbbProber(const long cache_size):
  m_lib_handle(nullptr),
  m_probe_egbb(nullptr),
  m_cache_size(cache_size)
{}

EgbbProber::~EgbbProber()
{
  if (m_lib_handle) {
    dlclose(m_lib_handle);
  }
}

Status EgbbProber::load_egbb(const string& egbb_path)
{
  m_lib_handle = dlopen(FLAGS_egbb_shared_library.c_str(), RTLD_LAZY);
  if (!m_lib_handle) {
    ostringstream oss;
    oss << "Could not load shared library " << FLAGS_egbb_shared_library;
    return Status::error(oss.str());
  }
  load_egbb_t load_egbb = load_egbb_t(long(dlsym(m_lib_handle, c_load_egbb_xmen)));
  if (!load_egbb) {
    ostringstream oss;
    oss << "Could not find symbol " << c_load_egbb_xmen << " in shared library " << FLAGS_egbb_shared_library;
    return Status::error(oss.str());
  }
  m_probe_egbb = probe_egbb_t(long(dlsym(m_lib_handle, c_probe_egbb_xmen)));
  if (!m_probe_egbb) {
    ostringstream oss;
    oss << "Could not find symbol " << c_probe_egbb_xmen << " in shared library " << FLAGS_egbb_shared_library;
    return Status::error(oss.str());
  }
  load_egbb(egbb_path.c_str(), m_cache_size, LOAD_5MEN);
  return Status::valid();
}

static const int c_max_pieces = 5;

bool EgbbProber::probe(const ChessBoard& board, int* const score) const
{
  if (board.occupied().number() > c_max_pieces || m_probe_egbb == nullptr) {
    return false;
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
  const ColorBoard& white_board = board.color_board(Color::White);
  ADD_PIECE(white_board.piece_board(PieceSet::c_rook_index), _WROOK);
  ADD_PIECE(white_board.piece_board(PieceSet::c_knight_index), _WKNIGHT);
  ADD_PIECE(white_board.piece_board(PieceSet::c_bishop_index), _WBISHOP);
  ADD_PIECE(white_board.piece_board(PieceSet::c_queen_index), _WQUEEN);
  ADD_PIECE(white_board.piece_board(PieceSet::c_king_index), _WKING);
  ADD_PIECE(white_board.piece_board(PieceSet::c_pawn_index), _WPAWN);
  const ColorBoard& black_board = board.color_board(Color::Black);
  ADD_PIECE(black_board.piece_board(PieceSet::c_rook_index), _WROOK);
  ADD_PIECE(black_board.piece_board(PieceSet::c_knight_index), _WKNIGHT);
  ADD_PIECE(black_board.piece_board(PieceSet::c_bishop_index), _WBISHOP);
  ADD_PIECE(black_board.piece_board(PieceSet::c_queen_index), _WQUEEN);
  ADD_PIECE(black_board.piece_board(PieceSet::c_king_index), _WKING);
  ADD_PIECE(black_board.piece_board(PieceSet::c_pawn_index), _WPAWN);
  pieces[count] = _EMPTY;
  squares[count] = board.ep_captures().first_position().index();
  const int found_score = m_probe_egbb(board.turn_color() == Color::White ? _WHITE : _BLACK, pieces, squares);
  if (found_score == c_not_found) {
    return false;
  }
  *score = found_score;
  return true;
}

void EgbbProber::cache_size(const long cache_size)
{
  m_cache_size = cache_size;
}

} // namespace olaf
