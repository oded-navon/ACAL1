#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MEMORY_IMAGE_MAX_SIZE (65536)
#define NUM_OF_REGS (8)
#define MAX_STR_LEN (1024)
#define HALT_OPCODE (24)
#define SUCCESS (0)
#define FAIL (-1)
#define TRACE_FILE ("trace.txt")
#define SRAM_OUT ("sram_out.txt")

typedef enum {
	inst_params_imm = 65535,        // 00000000000000001111111111111111
	inst_params_src1 = 458752,      // 00000000000001110000000000000000
	inst_params_src0 = 3670016,     // 00000000001110000000000000000000
	inst_params_dst = 29360128,     // 00000001110000000000000000000000
	inst_params_opcode = 1040187392 // 00111110000000000000000000000000
}inst_params;

typedef enum {
	inst_params_imm_shift = 0,        // 00000000000000001111111111111111
	inst_params_src1_shift = 16,      // 00000000000001110000000000000000
	inst_params_src0_shift = 19,     // 00000000001110000000000000000000
	inst_params_dst_shift = 22,     // 00000001110000000000000000000000
	inst_params_opcode_shift = 25 // 00111110000000000000000000000000
}inst_params_shift;

typedef enum {
	ADD = 0,
	SUB = 1,
	LSF = 2,
	RSF = 3,
	AND = 4,
	OR = 5,
	XOR = 6,
	LHI = 7,
	LD = 8,
	ST = 9,
	JLT = 16,
	JLE = 17,
	JEQ = 18,
	JNE = 19,
	JIN = 20,
	HLT = 24
}opcodes;

typedef struct {
	int src0;
	int src1;
	int original_inst;
	int pc_taken;
	int pc_of_inst;
} inst_trace;

typedef struct {
	int opcode;
	int imm;
	int src0_index;
	int src1_index;
	int dst_index;
	inst_trace* trace;
} inst;



int _memory_image_input[MEMORY_IMAGE_MAX_SIZE];
inst* _instructions[MEMORY_IMAGE_MAX_SIZE];
int _regs[NUM_OF_REGS];
int _pc;
char* trace_file;
char opcodes_str[32][5];
