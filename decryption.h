#ifndef DECRYPTION_H
#define DECRYPTION_H
#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <memory.h>
#include <getopt.h>
#include <ctype.h>

extern void decrypt_file( char *in_name, char *out_name, RSA *keypair );
extern void decryption (char *ifile, char *ofile, char *rfile);
#endif