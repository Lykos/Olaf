#include "olaf/rules/magicnumbers.h"

#include <array>
#include <cstdint>
#include <cassert>
#include <fstream>
#include <iostream>
#include <gflags/gflags.h>

DEFINE_string(move_table, "/usr/local/share/olaf/move_table.bin",
              "The lookup table for magic numbers for rooks and bishops.");

using namespace std;

namespace olaf
{

static MagicNumbers::MoveTable read_move_table()
{
  MagicNumbers::MoveTable result;
  ifstream file(FLAGS_move_table, ios::in | ios::binary | ios::ate);
  const int size = file.tellg();
  if (size != MagicNumbers::c_move_table_size * sizeof(uint64_t)) {
    cout << "Move table has invalid size " << size << "." << endl;
    cout << "If your move table resides in a place different from " << FLAGS_move_table
         << ", please set it with --move_table=/path/to/movetable." << endl;
    exit(1);
  }
  file.seekg(0, ios::beg);
  assert(size > 0);
  char* const bytes = reinterpret_cast<char*>(&(result[0]));
  file.read(bytes, size);
  file.close();
  return result;
}

const MagicNumbers::MoveTable MagicNumbers::c_move_table = read_move_table();

// static
const MagicNumbers::MagicTable MagicNumbers::c_rook_magic = {{
  {&(c_move_table[0]), 0x101010101017eULL, 0xa180022080400230ULL, 52},
  {&(c_move_table[4096]), 0x202020202027cULL, 0x40100040022000ULL, 53},
  {&(c_move_table[6144]), 0x404040404047aULL, 0x80088020001002ULL, 53},
  {&(c_move_table[8192]), 0x8080808080876ULL, 0x80080280841000ULL, 53},
  {&(c_move_table[10240]), 0x1010101010106eULL, 0x4200042010460008ULL, 53},
  {&(c_move_table[12288]), 0x2020202020205eULL, 0x4800a0003040080ULL, 53},
  {&(c_move_table[14336]), 0x4040404040403eULL, 0x400110082041008ULL, 53},
  {&(c_move_table[16384]), 0x8080808080807eULL, 0x8000a041000880ULL, 52},
  {&(c_move_table[20480]), 0x1010101017e00ULL, 0x10138001a080c010ULL, 53},
  {&(c_move_table[22528]), 0x2020202027c00ULL, 0x804008200480ULL, 54},
  {&(c_move_table[23552]), 0x4040404047a00ULL, 0x10011012000c0ULL, 54},
  {&(c_move_table[24576]), 0x8080808087600ULL, 0x22004128102200ULL, 54},
  {&(c_move_table[25600]), 0x10101010106e00ULL, 0x200081201200cULL, 54},
  {&(c_move_table[26624]), 0x20202020205e00ULL, 0x202a001048460004ULL, 54},
  {&(c_move_table[27648]), 0x40404040403e00ULL, 0x81000100420004ULL, 54},
  {&(c_move_table[28672]), 0x80808080807e00ULL, 0x4000800380004500ULL, 53},
  {&(c_move_table[30720]), 0x10101017e0100ULL, 0x208002904001ULL, 53},
  {&(c_move_table[32768]), 0x20202027c0200ULL, 0x90004040026008ULL, 54},
  {&(c_move_table[33792]), 0x40404047a0400ULL, 0x208808010002001ULL, 54},
  {&(c_move_table[34816]), 0x8080808760800ULL, 0x2002020020704940ULL, 54},
  {&(c_move_table[35840]), 0x101010106e1000ULL, 0x8048010008110005ULL, 54},
  {&(c_move_table[36864]), 0x202020205e2000ULL, 0x6820808004002200ULL, 54},
  {&(c_move_table[37888]), 0x404040403e4000ULL, 0xa80040008023011ULL, 54},
  {&(c_move_table[38912]), 0x808080807e8000ULL, 0xb1460000811044ULL, 53},
  {&(c_move_table[40960]), 0x101017e010100ULL, 0x4204400080008ea0ULL, 53},
  {&(c_move_table[43008]), 0x202027c020200ULL, 0xb002400180200184ULL, 54},
  {&(c_move_table[44032]), 0x404047a040400ULL, 0x2020200080100380ULL, 54},
  {&(c_move_table[45056]), 0x8080876080800ULL, 0x10080080100080ULL, 54},
  {&(c_move_table[46080]), 0x1010106e101000ULL, 0x2204080080800400ULL, 54},
  {&(c_move_table[47104]), 0x2020205e202000ULL, 0xa40080360080ULL, 54},
  {&(c_move_table[48128]), 0x4040403e404000ULL, 0x2040604002810b1ULL, 54},
  {&(c_move_table[49152]), 0x8080807e808000ULL, 0x8c218600004104ULL, 53},
  {&(c_move_table[51200]), 0x1017e01010100ULL, 0x8180004000402000ULL, 53},
  {&(c_move_table[53248]), 0x2027c02020200ULL, 0x488c402000401001ULL, 54},
  {&(c_move_table[54272]), 0x4047a04040400ULL, 0x4018a00080801004ULL, 54},
  {&(c_move_table[55296]), 0x8087608080800ULL, 0x1230002105001008ULL, 54},
  {&(c_move_table[56320]), 0x10106e10101000ULL, 0x8904800800800400ULL, 54},
  {&(c_move_table[57344]), 0x20205e20202000ULL, 0x42000c42003810ULL, 54},
  {&(c_move_table[58368]), 0x40403e40404000ULL, 0x8408110400b012ULL, 54},
  {&(c_move_table[59392]), 0x80807e80808000ULL, 0x18086182000401ULL, 53},
  {&(c_move_table[61440]), 0x17e0101010100ULL, 0x2240088020c28000ULL, 53},
  {&(c_move_table[63488]), 0x27c0202020200ULL, 0x1001201040c004ULL, 54},
  {&(c_move_table[64512]), 0x47a0404040400ULL, 0xa02008010420020ULL, 54},
  {&(c_move_table[65536]), 0x8760808080800ULL, 0x10003009010060ULL, 54},
  {&(c_move_table[66560]), 0x106e1010101000ULL, 0x4008008008014ULL, 54},
  {&(c_move_table[67584]), 0x205e2020202000ULL, 0x80020004008080ULL, 54},
  {&(c_move_table[68608]), 0x403e4040404000ULL, 0x282020001008080ULL, 54},
  {&(c_move_table[69632]), 0x807e8080808000ULL, 0x50000181204a0004ULL, 53},
  {&(c_move_table[71680]), 0x7e010101010100ULL, 0x102042111804200ULL, 53},
  {&(c_move_table[73728]), 0x7c020202020200ULL, 0x40002010004001c0ULL, 54},
  {&(c_move_table[74752]), 0x7a040404040400ULL, 0x19220045508200ULL, 54},
  {&(c_move_table[75776]), 0x76080808080800ULL, 0x20030010060a900ULL, 54},
  {&(c_move_table[76800]), 0x6e101010101000ULL, 0x8018028040080ULL, 54},
  {&(c_move_table[77824]), 0x5e202020202000ULL, 0x88240002008080ULL, 54},
  {&(c_move_table[78848]), 0x3e404040404000ULL, 0x10301802830400ULL, 54},
  {&(c_move_table[79872]), 0x7e808080808000ULL, 0x332a4081140200ULL, 53},
  {&(c_move_table[81920]), 0x7e01010101010100ULL, 0x8080010a601241ULL, 52},
  {&(c_move_table[86016]), 0x7c02020202020200ULL, 0x1008010400021ULL, 53},
  {&(c_move_table[88064]), 0x7a04040404040400ULL, 0x4082001007241ULL, 53},
  {&(c_move_table[90112]), 0x7608080808080800ULL, 0x211009001200509ULL, 53},
  {&(c_move_table[92160]), 0x6e10101010101000ULL, 0x8015001002441801ULL, 53},
  {&(c_move_table[94208]), 0x5e20202020202000ULL, 0x801000804000603ULL, 53},
  {&(c_move_table[96256]), 0x3e40404040404000ULL, 0xc0900220024a401ULL, 53},
  {&(c_move_table[98304]), 0x7e80808080808000ULL, 0x1000200608243ULL, 52}
}};

// static
const MagicNumbers::MagicTable MagicNumbers::c_bishop_magic = {{
  {&(c_move_table[102400]), 0x40201008040200ULL, 0x2910054208004104ULL, 58},
  {&(c_move_table[102464]), 0x402010080400ULL, 0x2100630a7020180ULL, 59},
  {&(c_move_table[102496]), 0x4020100a00ULL, 0x5822022042000000ULL, 59},
  {&(c_move_table[102528]), 0x40221400ULL, 0x2ca804a100200020ULL, 59},
  {&(c_move_table[102560]), 0x2442800ULL, 0x204042200000900ULL, 59},
  {&(c_move_table[102592]), 0x204085000ULL, 0x2002121024000002ULL, 59},
  {&(c_move_table[102624]), 0x20408102000ULL, 0x80404104202000e8ULL, 59},
  {&(c_move_table[102656]), 0x2040810204000ULL, 0x812a020205010840ULL, 58},
  {&(c_move_table[102720]), 0x20100804020000ULL, 0x8005181184080048ULL, 59},
  {&(c_move_table[102752]), 0x40201008040000ULL, 0x1001c20208010101ULL, 59},
  {&(c_move_table[102784]), 0x4020100a0000ULL, 0x1001080204002100ULL, 59},
  {&(c_move_table[102816]), 0x4022140000ULL, 0x1810080489021800ULL, 59},
  {&(c_move_table[102848]), 0x244280000ULL, 0x62040420010a00ULL, 59},
  {&(c_move_table[102880]), 0x20408500000ULL, 0x5028043004300020ULL, 59},
  {&(c_move_table[102912]), 0x2040810200000ULL, 0xc0080a4402605002ULL, 59},
  {&(c_move_table[102944]), 0x4081020400000ULL, 0x8a00a0104220200ULL, 59},
  {&(c_move_table[102976]), 0x10080402000200ULL, 0x940000410821212ULL, 59},
  {&(c_move_table[103008]), 0x20100804000400ULL, 0x1808024a280210ULL, 59},
  {&(c_move_table[103040]), 0x4020100a000a00ULL, 0x40c0422080a0598ULL, 57},
  {&(c_move_table[103168]), 0x402214001400ULL, 0x4228020082004050ULL, 57},
  {&(c_move_table[103296]), 0x24428002800ULL, 0x200800400e00100ULL, 57},
  {&(c_move_table[103424]), 0x2040850005000ULL, 0x20b001230021040ULL, 57},
  {&(c_move_table[103552]), 0x4081020002000ULL, 0x90a0201900c00ULL, 59},
  {&(c_move_table[103584]), 0x8102040004000ULL, 0x4940120a0a0108ULL, 59},
  {&(c_move_table[103616]), 0x8040200020400ULL, 0x20208050a42180ULL, 59},
  {&(c_move_table[103648]), 0x10080400040800ULL, 0x1004804b280200ULL, 59},
  {&(c_move_table[103680]), 0x20100a000a1000ULL, 0x2048020024040010ULL, 57},
  {&(c_move_table[103808]), 0x40221400142200ULL, 0x102c04004010200ULL, 55},
  {&(c_move_table[104320]), 0x2442800284400ULL, 0x20408204c002010ULL, 55},
  {&(c_move_table[104832]), 0x4085000500800ULL, 0x2411100020080c1ULL, 57},
  {&(c_move_table[104960]), 0x8102000201000ULL, 0x102a008084042100ULL, 59},
  {&(c_move_table[104992]), 0x10204000402000ULL, 0x941030000a09846ULL, 59},
  {&(c_move_table[105024]), 0x4020002040800ULL, 0x244100800400200ULL, 59},
  {&(c_move_table[105056]), 0x8040004081000ULL, 0x4000901010080696ULL, 59},
  {&(c_move_table[105088]), 0x100a000a102000ULL, 0x280404180020ULL, 57},
  {&(c_move_table[105216]), 0x22140014224000ULL, 0x800042008240100ULL, 55},
  {&(c_move_table[105728]), 0x44280028440200ULL, 0x220008400088020ULL, 55},
  {&(c_move_table[106240]), 0x8500050080400ULL, 0x4020182000904c9ULL, 57},
  {&(c_move_table[106368]), 0x10200020100800ULL, 0x23010400020600ULL, 59},
  {&(c_move_table[106400]), 0x20400040201000ULL, 0x41040020110302ULL, 59},
  {&(c_move_table[106432]), 0x2000204081000ULL, 0x412101004020818ULL, 59},
  {&(c_move_table[106464]), 0x4000408102000ULL, 0x8022080a09404208ULL, 59},
  {&(c_move_table[106496]), 0xa000a10204000ULL, 0x1401210240484800ULL, 57},
  {&(c_move_table[106624]), 0x14001422400000ULL, 0x22244208010080ULL, 57},
  {&(c_move_table[106752]), 0x28002844020000ULL, 0x1105040104000210ULL, 57},
  {&(c_move_table[106880]), 0x50005008040200ULL, 0x2040088800c40081ULL, 57},
  {&(c_move_table[107008]), 0x20002010080400ULL, 0x8184810252000400ULL, 59},
  {&(c_move_table[107040]), 0x40004020100800ULL, 0x4004610041002200ULL, 59},
  {&(c_move_table[107072]), 0x20408102000ULL, 0x40201a444400810ULL, 59},
  {&(c_move_table[107104]), 0x40810204000ULL, 0x4611010802020008ULL, 59},
  {&(c_move_table[107136]), 0xa1020400000ULL, 0x80000b0401040402ULL, 59},
  {&(c_move_table[107168]), 0x142240000000ULL, 0x20004821880a00ULL, 59},
  {&(c_move_table[107200]), 0x284402000000ULL, 0x8200002022440100ULL, 59},
  {&(c_move_table[107232]), 0x500804020000ULL, 0x9431801010068ULL, 59},
  {&(c_move_table[107264]), 0x201008040200ULL, 0x1040c20806108040ULL, 59},
  {&(c_move_table[107296]), 0x402010080400ULL, 0x804901403022a40ULL, 59},
  {&(c_move_table[107328]), 0x2040810204000ULL, 0x2400202602104000ULL, 58},
  {&(c_move_table[107392]), 0x4081020400000ULL, 0x208520209440204ULL, 59},
  {&(c_move_table[107424]), 0xa102040000000ULL, 0x40c000022013020ULL, 59},
  {&(c_move_table[107456]), 0x14224000000000ULL, 0x2000104000420600ULL, 59},
  {&(c_move_table[107488]), 0x28440200000000ULL, 0x400000260142410ULL, 59},
  {&(c_move_table[107520]), 0x50080402000000ULL, 0x800633408100500ULL, 59},
  {&(c_move_table[107552]), 0x20100804020000ULL, 0x2404080a1410ULL, 59},
  {&(c_move_table[107584]), 0x40201008040200ULL, 0x138200122002900ULL, 58}
}};

const MagicNumbers::SquareTable MagicNumbers::c_knight_table = {
  0x20400ULL,
  0x50800ULL,
  0xa1100ULL,
  0x142200ULL,
  0x284400ULL,
  0x508800ULL,
  0xa01000ULL,
  0x402000ULL,
  0x2040004ULL,
  0x5080008ULL,
  0xa110011ULL,
  0x14220022ULL,
  0x28440044ULL,
  0x50880088ULL,
  0xa0100010ULL,
  0x40200020ULL,
  0x204000402ULL,
  0x508000805ULL,
  0xa1100110aULL,
  0x1422002214ULL,
  0x2844004428ULL,
  0x5088008850ULL,
  0xa0100010a0ULL,
  0x4020002040ULL,
  0x20400040200ULL,
  0x50800080500ULL,
  0xa1100110a00ULL,
  0x142200221400ULL,
  0x284400442800ULL,
  0x508800885000ULL,
  0xa0100010a000ULL,
  0x402000204000ULL,
  0x2040004020000ULL,
  0x5080008050000ULL,
  0xa1100110a0000ULL,
  0x14220022140000ULL,
  0x28440044280000ULL,
  0x50880088500000ULL,
  0xa0100010a00000ULL,
  0x40200020400000ULL,
  0x204000402000000ULL,
  0x508000805000000ULL,
  0xa1100110a000000ULL,
  0x1422002214000000ULL,
  0x2844004428000000ULL,
  0x5088008850000000ULL,
  0xa0100010a0000000ULL,
  0x4020002040000000ULL,
  0x400040200000000ULL,
  0x800080500000000ULL,
  0x1100110a00000000ULL,
  0x2200221400000000ULL,
  0x4400442800000000ULL,
  0x8800885000000000ULL,
  0x100010a000000000ULL,
  0x2000204000000000ULL,
  0x4020000000000ULL,
  0x8050000000000ULL,
  0x110a0000000000ULL,
  0x22140000000000ULL,
  0x44280000000000ULL,
  0x88500000000000ULL,
  0x10a00000000000ULL,
  0x20400000000000ULL
};

const MagicNumbers::SquareTable MagicNumbers::c_king_table = {
  0x302ULL,
  0x705ULL,
  0xe0aULL,
  0x1c14ULL,
  0x3828ULL,
  0x7050ULL,
  0xe0a0ULL,
  0xc040ULL,
  0x30203ULL,
  0x70507ULL,
  0xe0a0eULL,
  0x1c141cULL,
  0x382838ULL,
  0x705070ULL,
  0xe0a0e0ULL,
  0xc040c0ULL,
  0x3020300ULL,
  0x7050700ULL,
  0xe0a0e00ULL,
  0x1c141c00ULL,
  0x38283800ULL,
  0x70507000ULL,
  0xe0a0e000ULL,
  0xc040c000ULL,
  0x302030000ULL,
  0x705070000ULL,
  0xe0a0e0000ULL,
  0x1c141c0000ULL,
  0x3828380000ULL,
  0x7050700000ULL,
  0xe0a0e00000ULL,
  0xc040c00000ULL,
  0x30203000000ULL,
  0x70507000000ULL,
  0xe0a0e000000ULL,
  0x1c141c000000ULL,
  0x382838000000ULL,
  0x705070000000ULL,
  0xe0a0e0000000ULL,
  0xc040c0000000ULL,
  0x3020300000000ULL,
  0x7050700000000ULL,
  0xe0a0e00000000ULL,
  0x1c141c00000000ULL,
  0x38283800000000ULL,
  0x70507000000000ULL,
  0xe0a0e000000000ULL,
  0xc040c000000000ULL,
  0x302030000000000ULL,
  0x705070000000000ULL,
  0xe0a0e0000000000ULL,
  0x1c141c0000000000ULL,
  0x3828380000000000ULL,
  0x7050700000000000ULL,
  0xe0a0e00000000000ULL,
  0xc040c00000000000ULL,
  0x203000000000000ULL,
  0x507000000000000ULL,
  0xa0e000000000000ULL,
  0x141c000000000000ULL,
  0x2838000000000000ULL,
  0x5070000000000000ULL,
  0xa0e0000000000000ULL,
  0x40c0000000000000ULL
};

const MagicNumbers::ColorSquareTable MagicNumbers::c_pawn_one_step_table = {
           0,          0,          0,          0,          0,          0,          0,          0,
  1ULL << 16, 1ULL << 17, 1ULL << 18, 1ULL << 19, 1ULL << 20, 1ULL << 21, 1ULL << 22, 1ULL << 23,
  1ULL << 24, 1ULL << 25, 1ULL << 26, 1ULL << 27, 1ULL << 28, 1ULL << 29, 1ULL << 30, 1ULL << 31,
  1ULL << 32, 1ULL << 33, 1ULL << 34, 1ULL << 35, 1ULL << 36, 1ULL << 37, 1ULL << 38, 1ULL << 39,
  1ULL << 40, 1ULL << 41, 1ULL << 42, 1ULL << 43, 1ULL << 44, 1ULL << 45, 1ULL << 46, 1ULL << 47,
  1ULL << 48, 1ULL << 49, 1ULL << 50, 1ULL << 51, 1ULL << 52, 1ULL << 53, 1ULL << 54, 1ULL << 55,
  1ULL << 56, 1ULL << 57, 1ULL << 58, 1ULL << 59, 1ULL << 60, 1ULL << 61, 1ULL << 62, 1ULL << 63,
           0,          0,          0,          0,          0,          0,          0,          0,

           0,          0,          0,          0,          0,          0,          0,          0,
   1ULL << 0,  1ULL << 1,  1ULL << 2,  1ULL << 3,  1ULL << 4,  1ULL << 5,  1ULL << 6,  1ULL << 7,
   1ULL << 8,  1ULL << 9, 1ULL << 10, 1ULL << 11, 1ULL << 12, 1ULL << 13, 1ULL << 14, 1ULL << 15,
  1ULL << 16, 1ULL << 17, 1ULL << 18, 1ULL << 19, 1ULL << 20, 1ULL << 21, 1ULL << 22, 1ULL << 23,
  1ULL << 24, 1ULL << 25, 1ULL << 26, 1ULL << 27, 1ULL << 28, 1ULL << 29, 1ULL << 30, 1ULL << 31,
  1ULL << 32, 1ULL << 33, 1ULL << 34, 1ULL << 35, 1ULL << 36, 1ULL << 37, 1ULL << 38, 1ULL << 39,
  1ULL << 40, 1ULL << 41, 1ULL << 42, 1ULL << 43, 1ULL << 44, 1ULL << 45, 1ULL << 46, 1ULL << 47,
           0,          0,          0,          0,          0,          0,          0,          0
};

const MagicNumbers::ColorSquareTable MagicNumbers::c_pawn_two_step_table = {
           0,          0,          0,          0,          0,          0,          0,          0,
  1ULL << 24, 1ULL << 25, 1ULL << 26, 1ULL << 27, 1ULL << 28, 1ULL << 29, 1ULL << 30, 1ULL << 31,
           0,          0,          0,          0,          0,          0,          0,          0,
           0,          0,          0,          0,          0,          0,          0,          0,
           0,          0,          0,          0,          0,          0,          0,          0,
           0,          0,          0,          0,          0,          0,          0,          0,
           0,          0,          0,          0,          0,          0,          0,          0,
           0,          0,          0,          0,          0,          0,          0,          0,

           0,          0,          0,          0,          0,          0,          0,          0,
           0,          0,          0,          0,          0,          0,          0,          0,
           0,          0,          0,          0,          0,          0,          0,          0,
           0,          0,          0,          0,          0,          0,          0,          0,
           0,          0,          0,          0,          0,          0,          0,          0,
           0,          0,          0,          0,          0,          0,          0,          0,
  1ULL << 32, 1ULL << 33, 1ULL << 34, 1ULL << 35, 1ULL << 36, 1ULL << 37, 1ULL << 38, 1ULL << 39,
           0,          0,          0,          0,          0,          0,          0,          0
};

// Shift the bit pattern 101 to the place in front of the pawn - 1, s.t. the 0 is directly in front.
// For the borders, use 100 and 001 instead.
const MagicNumbers::ColorSquareTable MagicNumbers::c_pawn_capture_table = {
           0,          0,          0,          0,          0,          0,          0,          0,
  4ULL << 15, 5ULL << 16, 5ULL << 17, 5ULL << 18, 5ULL << 19, 5ULL << 20, 5ULL << 21, 1ULL << 22,
  4ULL << 23, 5ULL << 24, 5ULL << 25, 5ULL << 26, 5ULL << 27, 5ULL << 28, 5ULL << 29, 1ULL << 30,
  4ULL << 31, 5ULL << 32, 5ULL << 33, 5ULL << 34, 5ULL << 35, 5ULL << 36, 5ULL << 37, 1ULL << 38,
  4ULL << 39, 5ULL << 40, 5ULL << 41, 5ULL << 42, 5ULL << 43, 5ULL << 44, 5ULL << 45, 1ULL << 46,
  4ULL << 47, 5ULL << 48, 5ULL << 49, 5ULL << 50, 5ULL << 51, 5ULL << 52, 5ULL << 53, 1ULL << 54,
  4ULL << 55, 5ULL << 56, 5ULL << 57, 5ULL << 58, 5ULL << 59, 5ULL << 60, 5ULL << 61, 1ULL << 62,
           0,          0,          0,          0,          0,          0,          0,          0,

           0,          0,          0,          0,          0,          0,          0,          0,
   4ULL >> 1,  5ULL << 0,  5ULL << 1,  5ULL << 2,  5ULL << 3,  5ULL << 4,  5ULL << 5,  1ULL << 6,
   4ULL << 7,  5ULL << 8,  5ULL << 9, 5ULL << 10, 5ULL << 11, 5ULL << 12, 5ULL << 13, 1ULL << 14,
  4ULL << 15, 5ULL << 16, 5ULL << 17, 5ULL << 18, 5ULL << 19, 5ULL << 20, 5ULL << 21, 1ULL << 22,
  4ULL << 23, 5ULL << 24, 5ULL << 25, 5ULL << 26, 5ULL << 27, 5ULL << 28, 5ULL << 29, 1ULL << 30,
  4ULL << 31, 5ULL << 32, 5ULL << 33, 5ULL << 34, 5ULL << 35, 5ULL << 36, 5ULL << 37, 1ULL << 38,
  4ULL << 39, 5ULL << 40, 5ULL << 41, 5ULL << 42, 5ULL << 43, 5ULL << 44, 5ULL << 45, 1ULL << 46,
           0,          0,          0,          0,          0,          0,          0,          0
};

const MagicNumbers::ColorTable MagicNumbers::c_promotion_rows = {
  0xFFULL << (7 * 8),
  0xFFULL
};

const MagicNumbers::ColorTable MagicNumbers::c_king_positions = {
  1ULL << 4,
  1ULL << (7 * 8 + 4)
};

const MagicNumbers::ColorTable MagicNumbers::c_castle_k_square = {
  1ULL << 6,
  1ULL << (7 * 8 + 6)
};

const MagicNumbers::ColorTable MagicNumbers::c_castle_q_square = {
  1ULL << 2,
  1ULL << (7 * 8 + 2)
};

const MagicNumbers::ColorTable MagicNumbers::c_castle_k_room = {
  3ULL << 5,
  3ULL << (7 * 8 + 5)
};

const MagicNumbers::ColorTable MagicNumbers::c_castle_q_room = {
  7ULL << 1,
  7ULL << (7 * 8 + 1)
};

const MagicNumbers::ColorTable MagicNumbers::c_castle_k_rook = {
  1ULL << 7,
  1ULL << (7 * 8 + 7),
};

const MagicNumbers::ColorTable MagicNumbers::c_castle_q_rook = {
  1ULL,
  1ULL << 7 * 8
};

} // namespace olaf
