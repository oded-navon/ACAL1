#pragma once
#define _CRT_SECURE_NO_WARNINGS


/*
This function parses the memory file.
The function returns the number of lines parsed
It also returns the memory read in the output_object
*/
int parse_memory_file(char* file_path);

/*
This function converts the raw hex lines read from memory to instructions
*/
int convert_mem_to_inst(int num_of_lines_read_from_memory);

