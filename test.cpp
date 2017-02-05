#include "test.h"

void test()
{
    const int key_size = 512;
    char publ_file[] = "test_public_key";
    char priv_file[] = "test_priv_key";
    char middle_file[] = "test_middle_key";
    char infile[] = "test_infile";
    char outfile[] = "test_outfile";

    generate_keys(key_size, publ_file, priv_file);
    encryption(infile, middle_file, publ_file); 
    decryption(middle_file, outfile, priv_file);
    compare_files(infile, outfile);

}

int compare_files(char* infile, char* outfile)
{
    FILE *f1;
    FILE *f2;
    char buf1; 
    char buf2;

    f1 = fopen( infile, "rt" );
    if (f1 == NULL)
    {
        printf("No such file!\n");
        return 0;
    } 

    f2 = fopen( outfile, "rt" );
    if (f2 == NULL)
    {
        printf("No such file!\n");
        return 0;
    } 
    while (!feof(f1) && !feof(f2)) {
        fread( &buf1, 1, sizeof(buf1), f1 );
        fread( &buf2, 1, sizeof(buf2), f2 );
        if (buf1 != buf2) {
            fclose(f1);
            fclose(f2);
            return 0;
        }
    }

    if (feof(f1) != feof(f2)) {
        fclose(f1);
        fclose(f2);
        return 0;
    }

    fclose(f1);
    fclose(f2);

    return 1;

}