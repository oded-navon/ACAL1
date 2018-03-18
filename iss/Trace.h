#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Utils.h"

int start_trace(char* trace_file, char* input_file, int num_of_lines_parsed);
int end_trace(char* trace_file, int cnt);
int print_trace(char* trace_file, inst* inst_cmd, int cnt, int* old_regs);
int write_memory_output(char * memout_file);