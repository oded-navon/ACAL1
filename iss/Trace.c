#pragma once

#include "Trace.h"

int print_line1(FILE* file, int cnt, inst* inst_cmd);
int print_line2(FILE* file, inst* inst_cmd);
int print_line3(FILE* file, inst* inst_cmd, int* old_regs);
int print_line4(FILE* file, int* old_regs);
int print_line5(FILE* file, inst* inst_cmd);

int start_trace(char* trace_file, char* input_file, int num_of_lines_parsed)
{
	int return_value = SUCCESS;
	FILE* file = fopen(trace_file, "w");
	if (file == NULL)
	{
		return FAIL;
	}

	int check_ret = 0;
	char line_to_print[MAX_STR_LEN];

	check_ret = sprintf(line_to_print,
			"program %s loaded, %d lines\n\n",
			input_file,
			num_of_lines_parsed
		);

	if (check_ret < 0)
	{
		return_value = FAIL;
	}

	check_ret = fprintf(file, line_to_print);
	if (check_ret < 0)
	{
		return_value = FAIL;
	}

	fclose(file);
	return return_value;
}

int print_trace(char* trace_file, inst* inst_cmd, int cnt, int* old_regs)
{
	int return_value = SUCCESS;
	FILE* file = fopen(trace_file, "a");
	if (file == NULL)
	{
		return FAIL;
	}

	if (print_line1(file, cnt, inst_cmd) == FAIL)
	{
		return_value = FAIL;
	}

	if (print_line2(file, inst_cmd) == FAIL)
	{
		return_value = FAIL;
	}

	if (print_line3(file, inst_cmd, old_regs) == FAIL)
	{
		return_value = FAIL;
	}

	if (print_line4(file, old_regs) == FAIL)
	{
		return_value = FAIL;
	}

	if (print_line5(file, inst_cmd) == FAIL)
	{
		return_value = FAIL;
	}

	fclose(file);
	return return_value;
}

int print_line1(FILE* file, int cnt, inst* inst_cmd)
{
	int return_value = SUCCESS;

	int check_ret = 0;
	char line_to_print[MAX_STR_LEN];

	check_ret = sprintf(line_to_print,
		"--- instruction %d (%04x) @ PC %d (%04d) -----------------------------------------------------------\n",
		cnt,
		cnt,
		inst_cmd->trace->pc_of_inst,
		inst_cmd->trace->pc_of_inst
	);

	if (check_ret < 0)
	{
		return_value = FAIL;
	}

	check_ret = fprintf(file, line_to_print);
	if (check_ret < 0)
	{
		return_value = FAIL;
	}

	return return_value;
}

int print_line2(FILE* file, inst* inst_cmd)
{
	int return_value = SUCCESS;

	int check_ret = 0;
	char line_to_print[MAX_STR_LEN];

	check_ret = sprintf(line_to_print,
		"pc = %04d, inst = %08x, opcode = %d (%s), dst = %d, src0 = %d, src1 = %d, immediate = %08x\n",
		inst_cmd->trace->pc_of_inst,
		inst_cmd->trace->original_inst,
		inst_cmd->opcode,
		opcodes_str[inst_cmd->opcode],
		inst_cmd->dst_index,
		inst_cmd->src0_index,
		inst_cmd->src1_index,
		inst_cmd->imm

	);

	if (check_ret < 0)
	{
		return_value = FAIL;
	}

	check_ret = fprintf(file, line_to_print);
	if (check_ret < 0)
	{
		return_value = FAIL;
	}

	return return_value;
}

int print_line3(FILE* file, inst* inst_cmd, int* old_regs)
{
	int return_value = SUCCESS;

	int check_ret = 0;
	char line_to_print[MAX_STR_LEN];

	check_ret = sprintf(line_to_print,
		"r[0] = %08x r[1] = %08x r[2] = %08x r[3] = %08x\n",
		old_regs[0],
		inst_cmd->imm,
		old_regs[2],
		old_regs[3]
	);

	if (check_ret < 0)
	{
		return_value = FAIL;
	}

	check_ret = fprintf(file, line_to_print);
	if (check_ret < 0)
	{
		return_value = FAIL;
	}

	return return_value;
}

int print_line4(FILE* file, int* old_regs)
{
	int return_value = SUCCESS;

	int check_ret = 0;
	char line_to_print[MAX_STR_LEN];

	check_ret = sprintf(line_to_print,
		"r[4] = %08x r[5] = %08x r[6] = %08x r[7] = %08x\n\n",
		old_regs[4],
		old_regs[5],
		old_regs[6],
		old_regs[7]
	);

	if (check_ret < 0)
	{
		return_value = FAIL;
	}

	check_ret = fprintf(file, line_to_print);
	if (check_ret < 0)
	{
		return_value = FAIL;
	}

	return return_value;
}

int print_line5(FILE* file, inst* inst_cmd)
{
	int return_value = SUCCESS;

	int check_ret = 0;
	char line_to_print[MAX_STR_LEN];

	switch (inst_cmd->opcode)
	{
	case ADD:
	case SUB:
	case LSF:
	case RSF:
	case AND:
	case OR:
	case XOR:
		check_ret = sprintf(line_to_print,
			">>>> EXEC: R[%d] = %d %s %d <<<<\n\n",
			inst_cmd->dst_index,
			inst_cmd->trace->src0,
			opcodes_str[inst_cmd->opcode],
			inst_cmd->trace->src1
		);
		break;

	case LHI:
		check_ret = sprintf(line_to_print,
			">>>> EXEC: R[%d] %s %d <<<<\n\n",
			inst_cmd->dst_index,
			opcodes_str[inst_cmd->opcode],
			inst_cmd->imm
		);
		break;

	case LD:
		check_ret = sprintf(line_to_print,
			">>>> EXEC: R[%d] = MEM[%d] = %08x <<<<\n\n",
			inst_cmd->dst_index,
			inst_cmd->trace->src1,// the value of the memory address
			inst_cmd->trace->src0 //the value in the memory address
		);
		break;

	case ST:
		check_ret = sprintf(line_to_print,
			">>>> EXEC: MEM[%d] = R[%d] = %08x <<<<\n\n",
			inst_cmd->trace->src1,// the value of the memory address
			inst_cmd->src0_index,
			inst_cmd->trace->src0 //the value in the memory address
		);
		break;

	case JLT:
	case JLE:
	case JEQ:
	case JNE:
		check_ret = sprintf(line_to_print,
			">>>> EXEC: %s %d, %d, %d <<<<\n\n",
			opcodes_str[inst_cmd->opcode],
			inst_cmd->trace->src0, 
			inst_cmd->trace->src1,
			inst_cmd->trace->pc_taken
		);
		break;

	case JIN:
		check_ret = sprintf(line_to_print,
			">>>> EXEC: %s %d <<<<\n\n",
			opcodes_str[inst_cmd->opcode],
			inst_cmd->trace->pc_taken
		);
		break;

	case HLT:
		check_ret = sprintf(line_to_print,
			">>>> EXEC: HALT at PC %04x <<<<\n",
			_pc
		);
		break;
	}

	if (check_ret < 0)
	{
		return_value = FAIL;
	}

	check_ret = fprintf(file, line_to_print);
	if (check_ret < 0)
	{
		return_value = FAIL;
	}

	return return_value;
}

int end_trace(char* trace_file, int cnt)
{
	int return_value = SUCCESS;

	FILE* file = fopen(trace_file, "a");
	if (file == NULL)
	{
		return FAIL;
	}

	int check_ret = 0;
	char line_to_print[MAX_STR_LEN];

	check_ret = sprintf(line_to_print,
			"sim finished at pc %d, %d instructions",
			_pc,
			cnt+1
		);

	if (check_ret < 0)
	{
		return_value = FAIL;
	}

	check_ret = fprintf(file, line_to_print);
	if (check_ret < 0)
	{
		return_value = FAIL;
	}
	fclose(file);

	return return_value;
}

int write_memory_output(char * memout_file)
{
	int return_value = SUCCESS;
	FILE* file = fopen(memout_file, "w");
	if (file == NULL)
	{
		return FAIL;
	}

	int check_ret = 0;
	for (int i = 0; i < MEMORY_IMAGE_MAX_SIZE; i++)
	{
		check_ret = fprintf(file, "%08x\n", _memory_image_input[i]);
		if (check_ret < 0)
		{
			return_value = FAIL;
			break;
		}
	}
	fclose(file);
	return return_value;
}