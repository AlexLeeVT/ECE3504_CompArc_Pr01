#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
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

// custom type definitions
typedef enum {R, I, J} format_t;
typedef pair<string, format_t> opcode_t;

// gloabl variables
bool hasError = false;
int currentLine = 1;

// tables
unordered_map<int, string> primary_code;
unordered_map<int, string> secondary_code;
unordered_map<int, string> register_names;

// lists
list<int> branchAddresses;

// initialize lookup table
void initializeMaps() {
    secondary_code[0x20] = "add";
    primary_code[0x08] = "addi";
    primary_code[0x09] = "addiu";
    secondary_code[0x21] = "addu";
    secondary_code[0x24] = "and";
    primary_code[0x0c] = "andi";
    primary_code[0x04] = "beq";
    primary_code[0x05] = "bne";
    primary_code[0x24] = "lbu";
    primary_code[0x25] = "lhu";
    primary_code[0x30] = "ll";
    primary_code[0x0f] = "lui";
    primary_code[0x23] = "lw";
    secondary_code[0x27] = "nor";
    secondary_code[0x25] = "or";
    primary_code[0x0d] = "ori";
    secondary_code[0x2a] = "slt";
    primary_code[0x0a] = "slti";
    primary_code[0x0b] = "sltiu";
    secondary_code[0x2b] = "sltu";
    secondary_code[0x00] = "sll";
    secondary_code[0x02] = "srl";
    primary_code[0x28] = "sb";
    primary_code[0x38] = "sc";
    primary_code[0x29] = "sh";
    primary_code[0x2b] = "sw";
    secondary_code[0x22] = "sub";
    secondary_code[0x23] = "subu";

    register_names[0] = "$zero";
    register_names[1] = "$at";
    register_names[2] = "$v0";
    register_names[3] = "$v1";
    register_names[4] = "$a0";
    register_names[5] = "$a1";
    register_names[6] = "$a2";
    register_names[7] = "$a3";
    register_names[8] = "$t0";
    register_names[9] = "$t1";
    register_names[10] = "$t2";
    register_names[11] = "$t3";
    register_names[12] = "$t4";
    register_names[13] = "$t5";
    register_names[14] = "$t6";
    register_names[15] = "$t7";
    register_names[16] = "$s0";
    register_names[17] = "$s1";
    register_names[18] = "$s2";
    register_names[19] = "$s3";
    register_names[20] = "$s4";
    register_names[21] = "$s5";
    register_names[22] = "$s6";
    register_names[23] = "$s7";
    register_names[24] = "$t8";
    register_names[25] = "$t9";
    register_names[26] = "$k0";
    register_names[27] = "$k1";
    register_names[28] = "$gp";
    register_names[29] = "$sp";
    register_names[30] = "$fp";
    register_names[31] = "$ra";
}

#endif