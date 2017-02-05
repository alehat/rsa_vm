#include <stdio.h>
#include <memory.h>
#include <getopt.h>
#include <ctype.h>
#include "generate_keys.h"
#include "encryption.h"
#include "decryption.h"

void help() 
{
    printf("RSA 1.0 by Vera Myshelova\n");
    printf("Options:\n");
    printf("  -g  Generate keypair\n");
    printf("      Arguments:\n");
    printf("        -n          Key size in bits (for example 1024)\n");
    printf("        -r filename Private key file name\n");
    printf("        -p filename Public key file name\n");
    printf("  -e  Encrypt file\n");
    printf("      Arguments:\n");
    printf("        -i filename Input file name\n");
    printf("        -o filename Output file name\n");
    printf("        -p filename Public key file name\n");
    printf("  -d  Decrypt file\n");
    printf("      Arguments:\n");
    printf("        -i filename Input file name\n");
    printf("        -o filename Output file name\n");
    printf("        -r filename Private key file name\n");
    printf("  -h  Show this help\n");
    return;
}

int main(int argc, char *argv[])
{
    enum {
        OPT_GenKeys = 1,
        OPT_Encrypt = 2,
        OPT_Decrypt = 3,
        OPT_Help = 4
    };
    char infile[1000], outfile[1000], priv_file[1000],publ_file[1000];
    int key_size;
    int opindex = 0;
    char c;
    opterr = 0;
    if (argc == 1) {
        printf("Error: no arguments passed.\n");
        help();
        return 0;
    }
    while ((c = getopt(argc, argv, "gedhp:r:n:i:o:")) != -1) {
        switch (c) {
            case 'g':
                opindex = OPT_GenKeys;
                break;
            case 'e':
                opindex = OPT_Encrypt;
                break;
            case 'd':
                opindex = OPT_Decrypt;
                break;
            case 'h':
                opindex = OPT_Help;
                break;
            case 'i':
                strcpy(infile, optarg);
                break;
            case 'o':
                strcpy(outfile,optarg);
                break;
            case 'r':
                strcpy(priv_file,optarg);
                break;
            case 'p':
                strcpy(publ_file,optarg);
                break;
            case 'n':
                key_size = atoi(optarg);
                break;
            case '?':
                if ((optopt == 'i') || (optopt == 'o') || (optopt == 'p') 
                     || (optopt == 'r') || (optopt == 'n'))
                    fprintf(stderr, "Option -%c requires an argument\n", optopt);
                else if (isprint(c))
                    fprintf(stderr, "Unknown option `-%c`\n", optopt);
                else
                    fprintf(stderr, "Unknown character `%c`\n", optopt);
                return 1;
            default:
                printf("SUUKA\n");
                break;
        }
    }
    
    switch (opindex) {
        case OPT_GenKeys: 
            generate_keys(key_size, publ_file, priv_file);
            break;
        case OPT_Encrypt:
            encryption(infile, outfile, publ_file);
            break;
        case OPT_Decrypt:
            decryption(infile, outfile, priv_file);
            break;
        case OPT_Help:
            help();
            break;
        default:
            abort();
            break;
    }
    return 0;
}
































