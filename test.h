#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <memory.h>
#include <getopt.h>
#include <ctype.h>
#include "generate_keys.h"
#include "encryption.h"
#include "decryption.h"

extern void test();
extern int compare_files(char* infile, char* outfile);
#endif