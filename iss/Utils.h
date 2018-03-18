#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <stdbool.h>
#include "Globals.c"

#define MEMORY_IMAGE_MAX_SIZE (65536)

#define MAX_STR_LEN (1024)

void run_cmd(inst* inst_cmd);
void free_all_inst(int num_of_inst);
void init_opcodes_str();