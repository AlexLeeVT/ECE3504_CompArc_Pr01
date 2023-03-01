#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <unordered_map>


// shift operations
#define OP_BITSHIFT     26
#define RS_BITSHIFT     21
#define RT_BITSHIFT     16
#define RD_BITSHIFT     11
#define SHAMT_BITSHIFT  6
#define FUNC_BITSHIFT   0
#define IMM_BITSHIFT    0
#define ADDR_BITSHIFT   0

// bitmask operations 
#define OP_BITMASK      (63 << 26)
#define RS_BITMASK      (31 << 21)
#define RT_BITMASK      (31 << 16)
#define RD_BITMASK      (31 << 11)
#define SHAMT_BITMASK   (31 << 6)
#define FUNC_BITMASK    (63)
#define IMM_BITMASK     (65535)
#define ADDR_BITMASK    (67108863)

#endif