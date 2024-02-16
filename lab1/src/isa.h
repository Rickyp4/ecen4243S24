/***************************************************************/
/*                                                             */
/*   RISC-V RV32 Instruction Level Simulator                   */
/*                                                             */
/*   ECEN 4243                                                 */
/*   Oklahoma State University                                 */
/*                                                             */
/***************************************************************/

#ifndef _SIM_ISA_H_
#define _SIM_ISA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

//
// MACRO: Check sign bit (sb) of (v) to see if negative
//   if no, just give number
//   if yes, sign extend (e.g., 0x80_0000 -> 0xFF80_0000)
//
#define SIGNEXT(v, sb) ((v) | (((v) & (1 << (sb))) ? ~((1 << (sb))-1) : 0))

int ADD (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int ADDI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int BNE (int Rs1, int Rs2, int Imm, int Funct3) {

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] != CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;

}

// I Instructions
int LB (int Rd, int Rs1, int Imm, int Funct3) {

  int effAddr = Rs1 + SIGNEXT(Imm, 12);
  int allignedAddr = 
  int readData = mem_read_32(effAddr);
  int offsetMask = 0x3;
  int offset = effAddr & offsetMask;
  int mask = 0xFF;
  mask = mask << (offset * 8);
  int modifiedData = mask & readData;
  nodifiedData = modifiedData >> (Imm * 8);
  mem_write_32(Rd, modifiedData);
}
int LH (int Rd, int Rs1, int Imm, int Funct3){

}
int LW (int Rd, int Rs1, int Imm, int Funct3);
int LBU (int Rd, int Rs1, int Imm, int Funct3);
int LHU (int Rd, int Rs1, int Imm, int Funct3);
int SLLI (int Rd, int Rs1, int Imm, int Funct3);
int SLTI (int Rd, int Rs1, int Imm, int Funct3);
int SLTIU (int Rd, int Rs1, int Imm, int Funct3);
int XORI (int Rd, int Rs1, int Imm, int Funct3);
int SRLI (int Rd, int Rs1, int Imm, int Funct3);
int SRAI (int Rd, int Rs1, int Imm, int Funct3);
int ORI (int Rd, int Rs1, int Imm, int Funct3);
int ANDI (int Rd, int Rs1, int Imm, int Funct3);

// U Instruction
int AUIPC (int Rd, int Rs1, int Imm);
int LUI (int Rd, int Rs1, int Imm, int Funct3);

// S Instruction
int SB (int Rs1, int Rs2, int Imm, int Funct3);
int SH (int Rs1, int Rs2, int Imm, int Funct3);
int SW (int Rs1, int Rs2, int Imm, int Funct3);

// R instruction
int SUB (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] - CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SLL (int Rd, int Rs1, int Rs2, int Funct3);
int SLT (int Rd, int Rs1, int Rs2, int Funct3);
int SLTU (int Rd, int Rs1, int Rs2, int Funct3);
int XOR (int Rd, int Rs1, int Rs2, int Funct3);
int SRL (int Rd, int Rs1, int Rs2, int Funct3);
int SRA (int Rd, int Rs1, int Rs2, int Funct3);
int OR (int Rd, int Rs1, int Rs2, int Funct3);
int AND (int Rd, int Rs1, int Rs2, int Funct3);

// B instructions
int BEQ (int Rs1,int Rs2,int Imm,int Funct3){

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] == CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;

}
int BLT (int Rs1,int Rs2,int Imm,int Funct3);{

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;

}
int BGE (int Rs1,int Rs2,int Imm,int Funct3){

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] >= CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;

}
int BLTU (int Rs1,int Rs2,int Imm,int Funct3){

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;

}
int BGEU (int Rs1,int Rs2,int Imm,int Funct3){

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] >= CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC - 4) + (SIGNEXT(Imm,13));
  return 0;

}

// I instruction
int JALR (int Rd, int Rs1, int Imm, int Funct3){

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur + 4;
  return 0;

}

// J instruction
int JAL (int Rd, int Funct3){

  int cur = 0;
  cur = CURRENT_STATE.PC + SIGNEXT(Imm,20);
  NEXT_STATE.REGS[Rd] = cur + 4;
  return 0;

}

int ECALL (char* i_){return 0;}

#endif
