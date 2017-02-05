#ifndef GENERATE_KEYS_H
#define GENERATE_KEYS_H
#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <memory.h>
#include <getopt.h>
#include <ctype.h>

extern void generate_keys(int key_length, char * pfile, char * rfile);

#endif