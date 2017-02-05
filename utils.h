#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <memory.h>
#include <getopt.h>
#include <ctype.h>

typedef unsigned char byte;

extern void show_err( int err );
extern int fsize( FILE *f );
extern char* key_to_str( BIO *key );
#endif