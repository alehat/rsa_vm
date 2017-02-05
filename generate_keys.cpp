#include "generate_keys.h"
#include "utils.h"

void generate_keys(int key_length, char * pfile, char * rfile)
{

    if ((key_length == 0) or (key_length >= 32768))
    {
        printf("Unsupported key lendth! Try again.\n");
        return;
    } 

    RSA *keypair = RSA_generate_key( key_length, 3, NULL, NULL );

    BIO *publ = BIO_new( BIO_s_mem() );
    BIO *pri = BIO_new( BIO_s_mem() );

    PEM_write_bio_RSAPublicKey( publ, keypair );
    PEM_write_bio_RSAPrivateKey( pri, keypair, NULL, NULL, 0, NULL, NULL );

    char *key;
    FILE *f;
    FILE *f1;

    key = key_to_str( pri );
    printf("\n");
    printf( "%s\n", key );
    printf( "Enter file name for save: " );
    printf("%s\n", rfile);
    f = fopen( rfile, "wt" );
    if (f == NULL)
    {
    printf("Enter file name!\n");
    return;
    } 
    fprintf( f, "%s", &key[0] );
    

    free( key );

    key = key_to_str( publ );
    printf("\n");
    printf( "%s\n", key );
    printf( "Enter file name for save: " );
    
    printf("%s\n", pfile);
    f1 = fopen( pfile, "wt" );
    if ((strcmp(pfile, rfile) == 0) or (f1 == NULL))
    {
        printf("Enter another file name!\n");
        return;
    }
     
    fprintf( f1, "%s", key );
    fclose(f);
    fclose(f1);

    free( key );
}