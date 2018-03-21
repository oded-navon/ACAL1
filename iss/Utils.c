#pragma once

#include "Utils.h"

void free_all_inst(int num_of_inst)
{
	for (int i = 0; i < num_of_inst; i++)
	{
		free(_instructions[i]->trace);
		free(_instructions[i]);
	}
}

void run_cmd(inst* inst_cmd)
{
	int temp0 = 0;
	int temp1 = 0;
	inst_cmd->trace->pc_of_inst = _pc;
	switch (inst_cmd->opcode)
	{
	case ADD:
		if (inst_cmd->src0_index == 1)
		{
			temp0 = inst_cmd->imm;
		}
		else
		{
			temp0 = _regs[inst_cmd->src0_index];
		}
		if (inst_cmd->src1_index == 1)
		{
			temp1 = inst_cmd->imm;
		}
		else
		{
			temp1 = _regs[inst_cmd->src1_index];
		}
		if (inst_cmd->dst_index > 1)
		{
			_regs[inst_cmd->dst_index] = temp0 + temp1;
		}
		_pc++;
		break;

	case SUB:
		if (inst_cmd->src0_index == 1)
		{
			temp0 = inst_cmd->imm;
		}
		else
		{
			temp0 = _regs[inst_cmd->src0_index];
		}
		if (inst_cmd->src1_index == 1)
		{
			temp1 = inst_cmd->imm;
		}
		else
		{
			temp1 = _regs[inst_cmd->src1_index];
		}
		if (inst_cmd->dst_index > 1)
		{
			_regs[inst_cmd->dst_index] = temp0 - temp1;
		}
		_pc++;
		break;

	case LSF:
		if (inst_cmd->src0_index == 1)
		{
			temp0 = inst_cmd->imm;
		}
		else
		{
			temp0 = _regs[inst_cmd->src0_index];
		}
		if (inst_cmd->src1_index == 1)
		{
			temp1 = inst_cmd->imm;
		}
		else
		{
			temp1 = _regs[inst_cmd->src1_index];
		}
		if (inst_cmd->dst_index > 1)
		{
			_regs[inst_cmd->dst_index] = temp0 << temp1;
		}
		_pc++;
		break;

	case RSF:
		if (inst_cmd->src0_index == 1)
		{
			temp0 = inst_cmd->imm;
		}
		else
		{
			temp0 = _regs[inst_cmd->src0_index];
		}
		if (inst_cmd->src1_index == 1)
		{
			temp1 = inst_cmd->imm;
		}
		else
		{
			temp1 = _regs[inst_cmd->src1_index];
		}
		if (inst_cmd->dst_index > 1)
		{
			_regs[inst_cmd->dst_index] = temp0 >> temp1;
		}
		_pc++;
		break;

	case AND:
		if (inst_cmd->src0_index == 1)
		{
			temp0 = inst_cmd->imm;
		}
		else
		{
			temp0 = _regs[inst_cmd->src0_index];
		}
		if (inst_cmd->src1_index == 1)
		{
			temp1 = inst_cmd->imm;
		}
		else
		{
			temp1 = _regs[inst_cmd->src1_index];
		}
		if (inst_cmd->dst_index > 1)
		{
			_regs[inst_cmd->dst_index] = temp0 & temp1;
		}
		_pc++;
		break;

	case OR:
		if (inst_cmd->src0_index == 1)
		{
			temp0 = inst_cmd->imm;
		}
		else
		{
			temp0 = _regs[inst_cmd->src0_index];
		}
		if (inst_cmd->src1_index == 1)
		{
			temp1 = inst_cmd->imm;
		}
		else
		{
			temp1 = _regs[inst_cmd->src1_index];
		}
		if (inst_cmd->dst_index > 1)
		{
			_regs[inst_cmd->dst_index] = temp0 | temp1;
		}
		_pc++;
		break;

	case XOR:
		if (inst_cmd->src0_index == 1)
		{
			temp0 = inst_cmd->imm;
		}
		else
		{
			temp0 = _regs[inst_cmd->src0_index];
		}
		if (inst_cmd->src1_index == 1)
		{
			temp1 = inst_cmd->imm;
		}
		else
		{
			temp1 = _regs[inst_cmd->src1_index];
		}
		if (inst_cmd->dst_index > 1)
		{
			_regs[inst_cmd->dst_index] = temp0 ^ temp1;
		}
		_pc++;
		break;

	case LHI:
		temp0 = (inst_cmd->imm) << 16;
		// we need to only load the imm into the high bits of dst 
		// and not override the lower bits of dst, so we use AND
		if (inst_cmd->dst_index > 1)
		{
			_regs[inst_cmd->dst_index] = _regs[inst_cmd->dst_index] & temp0;
		}
		_pc++;
		break;

	case LD:
		//if src1 is R1, we use the imm
		if (inst_cmd->src1_index == 1)
		{
			temp1 = inst_cmd->imm;
			temp0 = _memory_image_input[temp1];
		}
		else
		{
			temp1 = _regs[inst_cmd->src1_index];
			temp0 = _memory_image_input[temp1];
		}
		if (temp1 < MEMORY_IMAGE_MAX_SIZE)
		{
			if (inst_cmd->dst_index > 1)
			{
				_regs[inst_cmd->dst_index] = temp0;
			}
		}
		_pc++;
		break;

	case ST:
		//if src0 is R1, we write the imm
		if (inst_cmd->src0_index == 1)
		{
			temp0 = inst_cmd->imm;
		}
		else
		{
			temp0 = _regs[inst_cmd->src0_index];
		}
		// if src1 is R1, we write into the address represented by imm
		if (inst_cmd->src1_index == 1)
		{
			temp1 = inst_cmd->imm;
		}
		else
		{
			temp1 = _regs[inst_cmd->src1_index];
		}
		if (temp1 < MEMORY_IMAGE_MAX_SIZE)
		{
			_memory_image_input[temp1] = temp0;
		}
		_pc++;
		break;

	case JLT:
		//if src0 is R1, we use the imm
		if (inst_cmd->src0_index == 1)
		{
			temp0 = inst_cmd->imm;
		}
		else
		{
			temp0 = _regs[inst_cmd->src0_index];
		}
		//if src1 is R1, we use the imm
		if (inst_cmd->src1_index == 1)
		{
			temp1 = inst_cmd->imm;
		}
		else
		{
			temp1 = _regs[inst_cmd->src1_index];
		}

		if (temp0 < temp1)
		{
			_regs[7] = _pc;
			_pc = inst_cmd->imm;
		}
		else
		{
			_pc++;
		}
		break;

	case JLE:
		//if src0 is R1, we use the imm
		if (inst_cmd->src0_index == 1)
		{
			temp0 = inst_cmd->imm;
		}
		else
		{
			temp0 = _regs[inst_cmd->src0_index];
		}
		//if src1 is R1, we use the imm
		if (inst_cmd->src1_index == 1)
		{
			temp1 = inst_cmd->imm;
		}
		else
		{
			temp1 = _regs[inst_cmd->src1_index];
		}

		if (temp0 <= temp1)
		{
			_regs[7] = _pc;
			_pc = inst_cmd->imm;
		}
		else
		{
			_pc++;
		}
		break;

	case JEQ:
		//if src0 is R1, we use the imm
		if (inst_cmd->src0_index == 1)
		{
			temp0 = inst_cmd->imm;
		}
		else
		{
			temp0 = _regs[inst_cmd->src0_index];
		}
		//if src1 is R1, we use the imm
		if (inst_cmd->src1_index == 1)
		{
			temp1 = inst_cmd->imm;
		}
		else
		{
			temp1 = _regs[inst_cmd->src1_index];
		}

		if (temp0 == temp1)
		{
			_regs[7] = _pc;
			_pc = inst_cmd->imm;
		}
		else
		{
			_pc++;
		}
		break;

	case JNE:
		//if src0 is R1, we use the imm
		if (inst_cmd->src0_index == 1)
		{
			temp0 = inst_cmd->imm;
		}
		else
		{
			temp0 = _regs[inst_cmd->src0_index];
		}
		//if src1 is R1, we use the imm
		if (inst_cmd->src1_index == 1)
		{
			temp1 = inst_cmd->imm;
		}
		else
		{
			temp1 = _regs[inst_cmd->src1_index];
		}

		if (temp0 != temp1)
		{
			_regs[7] = _pc;
			_pc = inst_cmd->imm;
		}
		else
		{
			_pc++;
		}
		break;

	case JIN:
		//if src0 is R1, we use the imm
		if (inst_cmd->src0_index == 1)
		{
			temp0 = inst_cmd->imm;
		}
		else
		{
			temp0 = _regs[inst_cmd->src0_index];
		}
		_regs[7] = _pc;
		if (temp0 < MEMORY_IMAGE_MAX_SIZE)
		{
			_pc = temp0;
		}
		else
		{
			_pc++;
		}
		break;

	case HLT:
		break;
	default:
		_pc++;
		break;
	}
	inst_cmd->trace->pc_taken = _pc;
	inst_cmd->trace->src0 = temp0;
	inst_cmd->trace->src1 = temp1;
}

void init_opcodes_str()
{
	sprintf(opcodes_str[0], "ADD");
	sprintf(opcodes_str[1], "SUB");
	sprintf(opcodes_str[2], "LSF");
	sprintf(opcodes_str[3], "RSF");
	sprintf(opcodes_str[4], "AND");
	sprintf(opcodes_str[5], "OR");
	sprintf(opcodes_str[6], "XOR");
	sprintf(opcodes_str[7], "LHI");
	sprintf(opcodes_str[8], "LD");
	sprintf(opcodes_str[9], "ST");
	sprintf(opcodes_str[16], "JLT");
	sprintf(opcodes_str[17], "JLE");
	sprintf(opcodes_str[18], "JEQ");
	sprintf(opcodes_str[19], "JNE");
	sprintf(opcodes_str[20], "JIN");
	sprintf(opcodes_str[24], "HLT");
}