#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <memory.h>
#include <getopt.h>
#include <ctype.h>
#include "utils.h"

extern void encrypt_file( char *in_name, char *out_name, RSA *keypair );
extern void encryption (char *ifile, char *ofile, char *pfile);
#endif