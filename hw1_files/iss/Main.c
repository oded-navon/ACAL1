#include "Main.h"
#include "ArgParser.h"
#include "Trace.h"
#include "Utils.h"

/*
We took care of the following edge cases:
1. In LD\ST\JIN: the address in the register is larger than 2^16. We ignore the command and keep going to the next pc.
2. In case we got a bad opcode, we skip to the next pc. The trace will print the bad opcode and the opcode str will be empty.
3. In case the pc overflows 0xffff, we restart it to 0
4. If the dst registers is R0 or R1, we skip the instruction to the next pc.
*/

int main(int argc, char* argv[])
{
	int return_value = SUCCESS;
	int num_of_parsed_lines = parse_memory_file(argv[1]);
	int num_of_insts = convert_mem_to_inst(num_of_parsed_lines);
	_regs[0] = 0;
	return_value = start_trace(TRACE_FILE, argv[1], num_of_parsed_lines);
	init_opcodes_str();


	int cnt = 0, old_pc = 0;
	_pc = 0;
	while (true)
	{
		//restart pc in case it maxes out
		if (_pc == 0xffff)
		{
			_pc = 0;
		}
		if (_instructions[_pc]->opcode == HLT)
		{
			_instructions[_pc]->trace->pc_of_inst = _pc;
			if (print_trace(TRACE_FILE, _instructions[_pc], cnt, _regs) == FAIL)
			{
				return_value = FAIL;
			}
			if (end_trace(TRACE_FILE, cnt) == FAIL)
			{
				return_value = FAIL;
			}
			break;
		}
		old_pc = _pc;
		int old_regs[NUM_OF_REGS];
		memcpy(old_regs, _regs, sizeof(int)*NUM_OF_REGS);
		run_cmd(_instructions[_pc]);
		//the pc changed after running the inst, and we need to print the trace of the inst from the old pc
		//we also need to trace the registers before the inst execution
		if (print_trace(TRACE_FILE, _instructions[old_pc], cnt, old_regs) == FAIL)
		{
			return_value = FAIL;
		}
		cnt++;
	}
	if (write_memory_output(SRAM_OUT) == FAIL)
	{
		return_value = FAIL;
	}
	free_all_inst(num_of_insts);
	return return_value;
}
