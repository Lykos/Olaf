#include "generation.h"

#include "olaf/rules/pieceset.h"

#include <array>
#include <cassert>
#include <algorithm>
#include <deque>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ostream>
#include <iostream>
#include <fstream>
#include <gflags/gflags.h>

#include "olaf/rules/bitboard.h"
#include "olaf/rules/chessboard.h"

DEFINE_string(output_file, "", "If this is non-empty, the output will be written here.");

using namespace std;

namespace olaf
{
namespace generation
{

static const array<uint64_t, 64> c_magic_number_rook = {
  0xa180022080400230ULL,
  0x40100040022000ULL,
  0x80088020001002ULL,
  0x80080280841000ULL,
  0x4200042010460008ULL,
  0x4800a0003040080ULL,
  0x400110082041008ULL,
  0x8000a041000880ULL,
  0x10138001a080c010ULL,
  0x804008200480ULL,
  0x10011012000c0ULL,
  0x22004128102200ULL,
  0x200081201200cULL,
  0x202a001048460004ULL,
  0x81000100420004ULL,
  0x4000800380004500ULL,
  0x208002904001ULL,
  0x90004040026008ULL,
  0x208808010002001ULL,
  0x2002020020704940ULL,
  0x8048010008110005ULL,
  0x6820808004002200ULL,
  0xa80040008023011ULL,
  0xb1460000811044ULL,
  0x4204400080008ea0ULL,
  0xb002400180200184ULL,
  0x2020200080100380ULL,
  0x10080080100080ULL,
  0x2204080080800400ULL,
  0xa40080360080ULL,
  0x2040604002810b1ULL,
  0x8c218600004104ULL,
  0x8180004000402000ULL,
  0x488c402000401001ULL,
  0x4018a00080801004ULL,
  0x1230002105001008ULL,
  0x8904800800800400ULL,
  0x42000c42003810ULL,
  0x8408110400b012ULL,
  0x18086182000401ULL,
  0x2240088020c28000ULL,
  0x1001201040c004ULL,
  0xa02008010420020ULL,
  0x10003009010060ULL,
  0x4008008008014ULL,
  0x80020004008080ULL,
  0x282020001008080ULL,
  0x50000181204a0004ULL,
  0x102042111804200ULL,
  0x40002010004001c0ULL,
  0x19220045508200ULL,
  0x20030010060a900ULL,
  0x8018028040080ULL,
  0x88240002008080ULL,
  0x10301802830400ULL,
  0x332a4081140200ULL,
  0x8080010a601241ULL,
  0x1008010400021ULL,
  0x4082001007241ULL,
  0x211009001200509ULL,
  0x8015001002441801ULL,
  0x801000804000603ULL,
  0xc0900220024a401ULL,
  0x1000200608243ULL
};

static const array<uint64_t, 64> c_magic_number_bishop = {
  0x2910054208004104ULL,
  0x2100630a7020180ULL,
  0x5822022042000000ULL,
  0x2ca804a100200020ULL,
  0x204042200000900ULL,
  0x2002121024000002ULL,
  0x80404104202000e8ULL,
  0x812a020205010840ULL,
  0x8005181184080048ULL,
  0x1001c20208010101ULL,
  0x1001080204002100ULL,
  0x1810080489021800ULL,
  0x62040420010a00ULL,
  0x5028043004300020ULL,
  0xc0080a4402605002ULL,
  0x8a00a0104220200ULL,
  0x940000410821212ULL,
  0x1808024a280210ULL,
  0x40c0422080a0598ULL,
  0x4228020082004050ULL,
  0x200800400e00100ULL,
  0x20b001230021040ULL,
  0x90a0201900c00ULL,
  0x4940120a0a0108ULL,
  0x20208050a42180ULL,
  0x1004804b280200ULL,
  0x2048020024040010ULL,
  0x102c04004010200ULL,
  0x20408204c002010ULL,
  0x2411100020080c1ULL,
  0x102a008084042100ULL,
  0x941030000a09846ULL,
  0x244100800400200ULL,
  0x4000901010080696ULL,
  0x280404180020ULL,
  0x800042008240100ULL,
  0x220008400088020ULL,
  0x4020182000904c9ULL,
  0x23010400020600ULL,
  0x41040020110302ULL,
  0x412101004020818ULL,
  0x8022080a09404208ULL,
  0x1401210240484800ULL,
  0x22244208010080ULL,
  0x1105040104000210ULL,
  0x2040088800c40081ULL,
  0x8184810252000400ULL,
  0x4004610041002200ULL,
  0x40201a444400810ULL,
  0x4611010802020008ULL,
  0x80000b0401040402ULL,
  0x20004821880a00ULL,
  0x8200002022440100ULL,
  0x9431801010068ULL,
  0x1040c20806108040ULL,
  0x804901403022a40ULL,
  0x2400202602104000ULL,
  0x208520209440204ULL,
  0x40c000022013020ULL,
  0x2000104000420600ULL,
  0x400000260142410ULL,
  0x800633408100500ULL,
  0x2404080a1410ULL,
  0x138200122002900ULL
};

static const array<uint64_t, 64> c_occupancy_mask_rook = {
  0x101010101017eULL,
  0x202020202027cULL,
  0x404040404047aULL,
  0x8080808080876ULL,
  0x1010101010106eULL,
  0x2020202020205eULL,
  0x4040404040403eULL,
  0x8080808080807eULL,
  0x1010101017e00ULL,
  0x2020202027c00ULL,
  0x4040404047a00ULL,
  0x8080808087600ULL,
  0x10101010106e00ULL,
  0x20202020205e00ULL,
  0x40404040403e00ULL,
  0x80808080807e00ULL,
  0x10101017e0100ULL,
  0x20202027c0200ULL,
  0x40404047a0400ULL,
  0x8080808760800ULL,
  0x101010106e1000ULL,
  0x202020205e2000ULL,
  0x404040403e4000ULL,
  0x808080807e8000ULL,
  0x101017e010100ULL,
  0x202027c020200ULL,
  0x404047a040400ULL,
  0x8080876080800ULL,
  0x1010106e101000ULL,
  0x2020205e202000ULL,
  0x4040403e404000ULL,
  0x8080807e808000ULL,
  0x1017e01010100ULL,
  0x2027c02020200ULL,
  0x4047a04040400ULL,
  0x8087608080800ULL,
  0x10106e10101000ULL,
  0x20205e20202000ULL,
  0x40403e40404000ULL,
  0x80807e80808000ULL,
  0x17e0101010100ULL,
  0x27c0202020200ULL,
  0x47a0404040400ULL,
  0x8760808080800ULL,
  0x106e1010101000ULL,
  0x205e2020202000ULL,
  0x403e4040404000ULL,
  0x807e8080808000ULL,
  0x7e010101010100ULL,
  0x7c020202020200ULL,
  0x7a040404040400ULL,
  0x76080808080800ULL,
  0x6e101010101000ULL,
  0x5e202020202000ULL,
  0x3e404040404000ULL,
  0x7e808080808000ULL,
  0x7e01010101010100ULL,
  0x7c02020202020200ULL,
  0x7a04040404040400ULL,
  0x7608080808080800ULL,
  0x6e10101010101000ULL,
  0x5e20202020202000ULL,
  0x3e40404040404000ULL,
  0x7e80808080808000ULL
};

static const array<uint64_t, 64> c_occupancy_mask_bishop = {
  0x40201008040200ULL,
  0x402010080400ULL,
  0x4020100a00ULL,
  0x40221400ULL,
  0x2442800ULL,
  0x204085000ULL,
  0x20408102000ULL,
  0x2040810204000ULL,
  0x20100804020000ULL,
  0x40201008040000ULL,
  0x4020100a0000ULL,
  0x4022140000ULL,
  0x244280000ULL,
  0x20408500000ULL,
  0x2040810200000ULL,
  0x4081020400000ULL,
  0x10080402000200ULL,
  0x20100804000400ULL,
  0x4020100a000a00ULL,
  0x402214001400ULL,
  0x24428002800ULL,
  0x2040850005000ULL,
  0x4081020002000ULL,
  0x8102040004000ULL,
  0x8040200020400ULL,
  0x10080400040800ULL,
  0x20100a000a1000ULL,
  0x40221400142200ULL,
  0x2442800284400ULL,
  0x4085000500800ULL,
  0x8102000201000ULL,
  0x10204000402000ULL,
  0x4020002040800ULL,
  0x8040004081000ULL,
  0x100a000a102000ULL,
  0x22140014224000ULL,
  0x44280028440200ULL,
  0x8500050080400ULL,
  0x10200020100800ULL,
  0x20400040201000ULL,
  0x2000204081000ULL,
  0x4000408102000ULL,
  0xa000a10204000ULL,
  0x14001422400000ULL,
  0x28002844020000ULL,
  0x50005008040200ULL,
  0x20002010080400ULL,
  0x40004020100800ULL,
  0x20408102000ULL,
  0x40810204000ULL,
  0xa1020400000ULL,
  0x142240000000ULL,
  0x284402000000ULL,
  0x500804020000ULL,
  0x201008040200ULL,
  0x402010080400ULL,
  0x2040810204000ULL,
  0x4081020400000ULL,
  0xa102040000000ULL,
  0x14224000000000ULL,
  0x28440200000000ULL,
  0x50080402000000ULL,
  0x20100804020000ULL,
  0x40201008040200ULL
};

static const array<int_fast8_t, 64> c_magic_number_shifts_rook = {
  52,53,53,53,53,53,53,52,
  53,54,54,54,54,54,54,53,
  53,54,54,54,54,54,54,53,
  53,54,54,54,54,54,54,53,
  53,54,54,54,54,54,54,53,
  53,54,54,54,54,54,54,53,
  53,54,54,54,54,54,54,53,
  52,53,53,53,53,53,53,52
};

static const array<int_fast8_t, 64> c_magic_number_shifts_bishop = {
  58,59,59,59,59,59,59,58,
  59,59,59,59,59,59,59,59,
  59,59,57,57,57,57,59,59,
  59,59,57,55,55,57,59,59,
  59,59,57,55,55,57,59,59,
  59,59,57,57,57,57,59,59,
  59,59,59,59,59,59,59,59,
  58,59,59,59,59,59,59,58
};

vector<int> indices(const uint64_t bits)
{
  vector<int> result;
  for (BitBoard bit_board(bits); bit_board; ) {
    result.push_back(bit_board.next_position().index());
  }
  return result;
}

static array<vector<uint64_t>, 64> occupancy_variation_rook;
static array<vector<uint64_t>, 64> occupancy_attack_set_rook;
static array<vector<uint64_t>, 64> occupancy_variation_bishop;
static array<vector<uint64_t>, 64> occupancy_attack_set_bishop;

void generate_occupancy_variations(const bool is_rook)
{
  int i;
  int bit_ref;
  int j;
  long mask;
  vector<int> set_bits_in_mask;
  vector<int> set_bits_in_index;
  array<int, 64> bit_count;
  array<vector<uint64_t>, 64>& occupancy_variation = is_rook ? occupancy_variation_rook : occupancy_variation_bishop;
  array<vector<uint64_t>, 64>& occupancy_attack_set = is_rook ? occupancy_attack_set_rook : occupancy_attack_set_bishop;

  for (bit_ref=0; bit_ref<=63; bit_ref++)
  {
    mask = is_rook ? c_occupancy_mask_rook[bit_ref] : c_occupancy_mask_bishop[bit_ref];
    set_bits_in_mask = indices(mask);
    bit_count[bit_ref] = BitBoard(mask).number();
    int variation_count = (int)(1L << bit_count[bit_ref]);
    occupancy_variation[bit_ref].resize(variation_count);
    occupancy_attack_set[bit_ref].resize(variation_count);
    for (i = 0; i < variation_count; i++)
    {
      assert(bit_ref < int(occupancy_variation.size()));
      assert(i < int(occupancy_variation[bit_ref].size()));
      assert(bit_ref < int(occupancy_attack_set.size()));
      assert(i < int(occupancy_attack_set[bit_ref].size()));
      occupancy_variation[bit_ref][i] = 0;

      // find bits set in index "i" and map them to bits in the 64 bit "occupancy_variation"
      set_bits_in_index = indices(i); // an array of integers showing which bits are set
      for (j = 0; j < static_cast<int>(set_bits_in_index.size()); j++)
      {
        occupancy_variation[bit_ref][i] |= (1L << set_bits_in_mask[set_bits_in_index[j]]);
      }

      if (is_rook)
      {
        for (j = bit_ref+8; j<=55 && (occupancy_variation[bit_ref][i] & (1L << j)) == 0; j+=8);
        if (j>=0 && j<=63) occupancy_attack_set[bit_ref][i] |= (1L << j);
        for (j = bit_ref-8; j>=8 && (occupancy_variation[bit_ref][i] & (1L << j)) == 0; j-=8);
        if (j>=0 && j<=63) occupancy_attack_set[bit_ref][i] |= (1L << j);
        for (j = bit_ref+1; j%8!=7 && j%8!=0 && (occupancy_variation[bit_ref][i] & (1L << j)) == 0; j++);
        if (j>=0 && j<=63) occupancy_attack_set[bit_ref][i] |= (1L << j);
        for (j = bit_ref-1; j%8!=7 && j%8!=0 && j>=0 && (occupancy_variation[bit_ref][i] & (1L << j)) == 0; j--);
        if (j>=0 && j<=63) occupancy_attack_set[bit_ref][i] |= (1L << j);
      }
      else
      {
        for (j = bit_ref+9; j%8!=7 && j%8!=0 && j<=55 && (occupancy_variation[bit_ref][i] & (1L << j)) == 0; j+=9);
        if (j>=0 && j<=63) occupancy_attack_set[bit_ref][i] |= (1L << j);
        for (j = bit_ref-9; j%8!=7 && j%8!=0 && j>=8 && (occupancy_variation[bit_ref][i] & (1L << j)) == 0; j-=9);
        if (j>=0 && j<=63) occupancy_attack_set[bit_ref][i] |= (1L << j);
        for (j = bit_ref+7; j%8!=7 && j%8!=0 && j<=55 && (occupancy_variation[bit_ref][i] & (1L << j)) == 0; j+=7);
        if (j>=0 && j<=63) occupancy_attack_set[bit_ref][i] |= (1L << j);
        for (j = bit_ref-7; j%8!=7 && j%8!=0 && j>=8 && (occupancy_variation[bit_ref][i] & (1L << j)) == 0; j-=7);
        if (j>=0 && j<=63) occupancy_attack_set[bit_ref][i] |= (1L << j);
      }
    }
  }
}

static array<vector<uint64_t>, 64> magic_moves_rook;

static array<vector<uint64_t>, 64> magic_moves_bishop;

void force_insert(vector<uint64_t>& vec, unsigned int i, uint64_t val)
{
  if (i >= vec.size()) {
    vec.resize(i + 1);
  }
  vec[i] = val;
}

void generate_move_database(const bool is_rook)
{
  array<vector<uint64_t>, 64>& occupancy_variation = is_rook ? occupancy_variation_rook : occupancy_variation_bishop;
  uint64_t valid_moves;
  int variations, bit_count;
  int bit_ref, i, j, magic_index;

  for (bit_ref=0; bit_ref<=63; bit_ref++)
  {
    bit_count = BitBoard(is_rook ? c_occupancy_mask_rook[bit_ref] : c_occupancy_mask_bishop[bit_ref]).number();
    variations = (int)(1L << bit_count);

    for (i = 0; i<variations; i++)
    {
      valid_moves = 0;
      if (is_rook)
      {
        magic_index = (uint64_t)((occupancy_variation[bit_ref][i] * c_magic_number_rook[bit_ref]) >> c_magic_number_shifts_rook[bit_ref]);

        for (j = bit_ref+8; j<=63; j+=8) { valid_moves |= (1L << j); if ((occupancy_variation[bit_ref][i] & (1L << j)) != 0) break; }
        for (j = bit_ref-8; j>=0; j-=8) { valid_moves |= (1L << j); if ((occupancy_variation[bit_ref][i] & (1L << j)) != 0) break; }
        for (j = bit_ref+1; j%8!=0; j++) { valid_moves |= (1L << j); if ((occupancy_variation[bit_ref][i] & (1L << j)) != 0) break; }
        for (j = bit_ref-1; j%8!=7 && j>=0; j--) { valid_moves |= (1L << j); if ((occupancy_variation[bit_ref][i] & (1L << j)) != 0) break; }

        force_insert(magic_moves_rook[bit_ref], magic_index, valid_moves);
      }
      else
      {
        magic_index = (uint64_t)((occupancy_variation[bit_ref][i] * c_magic_number_bishop[bit_ref]) >> c_magic_number_shifts_bishop[bit_ref]);

        for (j = bit_ref+9; j%8!=0 && j<=63; j+=9) { valid_moves |= (1L << j); if ((occupancy_variation[bit_ref][i] & (1L << j)) != 0) break; }
        for (j = bit_ref-9; j%8!=7 && j>=0; j-=9) { valid_moves |= (1L << j); if ((occupancy_variation[bit_ref][i] & (1L << j)) != 0) break; }
        for (j = bit_ref+7; j%8!=7 && j<=63; j+=7) {
          valid_moves |= (1L << j);
          if ((occupancy_variation[bit_ref][i] & (1L << j)) != 0)
            break;
        }
        for (j = bit_ref-7; j%8!=0 && j>=0; j-=7) {
          valid_moves |= (1L << j);
          if ((occupancy_variation[bit_ref][i] & (1L << j)) != 0)
            break;
        }

        force_insert(magic_moves_bishop[bit_ref], magic_index, valid_moves);
      }
    }
  }
}

struct Magic {
  int index;
  uint64_t mask;
  uint64_t magic;
  int shift;
};

ostream& operator <<(ostream& out, const Magic& magic)
{
  return out << "{&(c_move_table[" << dec << magic.index << "]), "
             << "0x" << hex << magic.mask << "ULL, "
             << "0x" << hex << magic.magic << "ULL, "
             << dec << magic.shift << "}";
}

static vector<uint64_t> optimized_magic_moves;

bool try_integrate(const vector<uint64_t>& moves, int index, array<Magic, 64>* const magic)
{
  auto it = search(optimized_magic_moves.begin(), optimized_magic_moves.end(),
                   moves.begin(), moves.end());
  if (it != optimized_magic_moves.end()) {
    cout << "Hit!";
    (*magic)[index].index = it - optimized_magic_moves.begin();
    return true;
  } else {
    return false;
  }
}

int back_overlap(const vector<uint64_t>& moves)
{
  auto end = optimized_magic_moves.end();
  auto it = moves.size() < optimized_magic_moves.size() ? end - moves.size() : optimized_magic_moves.begin();
  while (it != end) {
    ++it;
    it = find(it, end, moves.front());
    if (equal(it, end, moves.begin())) {
      return end - it;
    }
  }
  return 0;
}

void optimize_move_database(const array<vector<uint64_t>, 64>& magic_moves, array<Magic, 64>* const magic)
{
  for (int i = 0; i < 64; ++i) {
    const vector<uint64_t>& moves = magic_moves[i];
    if (!try_integrate(moves, i, magic)) {
      int overlap = back_overlap(moves);
      optimized_magic_moves.insert(optimized_magic_moves.end(), moves.begin() + overlap, moves.end());
      (*magic)[i].index = optimized_magic_moves.size() - moves.size();
    }
  }
}

static array<Magic, 64> rook_magic;
static array<Magic, 64> bishop_magic;

void optimize_move_database(const bool is_rook)
{
  if (is_rook) {
    optimize_move_database(magic_moves_rook, &rook_magic);
  } else {
    optimize_move_database(magic_moves_bishop, &bishop_magic);
  }
}

void finish_magic(const bool is_rook)
{
  for (int i = 0; i < 64; ++i)  {
    if (is_rook) {
      rook_magic[i].shift = c_magic_number_shifts_rook[i];
      rook_magic[i].mask = c_occupancy_mask_rook[i];
      rook_magic[i].magic = c_magic_number_rook[i];
    } else {
      bishop_magic[i].shift = c_magic_number_shifts_bishop[i];
      bishop_magic[i].mask = c_occupancy_mask_bishop[i];
      bishop_magic[i].magic = c_magic_number_bishop[i];
    }
  }
}

void print(uint64_t bla)
{
  cout << bla << endl;
  for (int i = 7; i >= 0; --i) {
    for (int j = 0; j < 8; ++j) {
      cout << ((bla >> (i * 8 + j)) & 1);
    }
    cout << endl;
  }
}

uint64_t do_magic(const Position position, const uint64_t board, const bool is_rook)
{
  const Magic& magic = (is_rook ? rook_magic : bishop_magic)[position.index()];
  return optimized_magic_moves[magic.index + (((board & magic.mask) * magic.magic) >> magic.shift)];
}

void print_magic(const bool is_rook)
{
  cout << endl;
  cout << "// static" << endl;
  cout << "const array<Magic, 64> MagicNumbers::c_" << (is_rook ? "rook" : "bishop") << "_magic = {{" << endl;
  auto magics = (is_rook ? rook_magic : bishop_magic);
  for (int i = 0; i < 63; ++i) {
    cout << "  " << magics[i] << "," << endl;
  }
  cout << "  " << magics[63] << endl;
  cout << "}};" << endl;
}

void generate_magic()
{
  cout << "Generating occupancy for rook" << endl;
  generate_occupancy_variations(true);
  cout << "Generating move database for rook" << endl;
  generate_move_database(true);
  cout << "Optimizing move database for rook" << endl;
  optimize_move_database(true);
  cout << "Finishing magic for rook" << endl;
  finish_magic(true);
  cout << "Generating occupancy for bishop" << endl;
  generate_occupancy_variations(false);
  cout << "Generating move database for bishop" << endl;
  generate_move_database(false);
  cout << "Optimizing move database for bishop" << endl;
  optimize_move_database(false);
  cout << "Finishing magic for bishop" << endl;
  finish_magic(false);
  cout << "Entries: " << optimized_magic_moves.size() << endl;
  int unoptimized_size = 0;
  for (int i = 0; i < 64; ++i) {
    unoptimized_size += magic_moves_bishop[i].size() + magic_moves_rook[i].size();
  }
  cout << "Unoptimized entries: " << unoptimized_size << endl << endl;
  print(do_magic(Position("a8"), 18446462598732972029ull, true));
  cout << endl;
  print(do_magic(Position("b2"), 1 << 18, false));
  cout << endl;
  if (!FLAGS_output_file.empty()) {
    ofstream file(FLAGS_output_file, ios::binary | ios::trunc | ios::out);
    const char* const block = reinterpret_cast<char*>(&(optimized_magic_moves[0]));
    file.write(block, optimized_magic_moves.size() * sizeof(uint64_t));
    file.close();
    cout << "File written." << endl;
  }
  print_magic(true);
  print_magic(false);
}

} // namespace generation
} // namespace olaf
