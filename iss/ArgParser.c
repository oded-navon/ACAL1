#include "ArgParser.h"
#include "Utils.h"

int parse_hex_number(char* hex_number);

int parse_memory_file(char* file_path)
{
	bool return_value = true;
	FILE* file = fopen(file_path, "r");
	if (file == NULL)
	{
		return false;
	}

	char* line = (char*)malloc(MAX_STR_LEN);
	int cnt = 0;
	while (fgets(line, MAX_STR_LEN, file) != NULL)
	{
		int parsed_line = parse_hex_number(line);
		_memory_image_input[cnt] = parsed_line;

		memset(line, 0, MAX_STR_LEN);
		cnt++;
	}

	fclose(file);
	free(line);
	return cnt;
}

int parse_hex_number(char* hex_number)
{
	return (int)strtol(hex_number, NULL, 16);
}

int convert_mem_to_inst(int num_of_lines_read_from_memory)
{
	int i;
	for (i = 0; i < num_of_lines_read_from_memory; i++)
	{
		// Check first what is the opcode of the inst, in case it's a HALT inst
		_instructions[i] = malloc(sizeof(inst));
		_instructions[i]->trace = malloc(sizeof(inst_trace));
		_instructions[i]->opcode = (_memory_image_input[i] & inst_params_opcode) >> inst_params_opcode_shift;

		_instructions[i]->imm = _memory_image_input[i] & inst_params_imm;
		_instructions[i]->src1_index = (_memory_image_input[i] & inst_params_src1) >> inst_params_src1_shift;
		_instructions[i]->src0_index = (_memory_image_input[i] & inst_params_src0) >> inst_params_src0_shift;
		_instructions[i]->dst_index = (_memory_image_input[i] & inst_params_dst) >> inst_params_dst_shift;
		_instructions[i]->trace->original_inst = _memory_image_input[i];

		if (_instructions[i]->opcode == HALT_OPCODE)
		{
			// The other fields of the struct are already initialized to 0 so it's ok to break
			break;
		}
	}

	// return the number of instructions found including HALT
	return i + 1;
}