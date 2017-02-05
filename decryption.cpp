
#include "decryption.h"
#include "utils.h"

void decrypt_file( char *in_name, char *out_name, RSA *keypair )
{
    FILE *in = fopen( in_name, "rb" );
    FILE *out = fopen( out_name, "wb" );

    int l = RSA_size(keypair), r, r2;

    byte *in_buf = (byte*) malloc( l + 1 );
    byte *decrypt = (byte*) malloc( l );

    while (!feof(in))
    {
        r = fread( in_buf, 1, l, in );
        if (r != l) break;

        r2 = RSA_private_decrypt( r, in_buf, decrypt, keypair, RSA_PKCS1_OAEP_PADDING );

        printf( "  decrypt: %d/%d\n", r, r2 );

        if (r2 == -1)
        {
            show_err(r2);
            return;
        }

        fwrite( decrypt, 1, r2, out );

    }

    fclose(in);
    fclose(out);
}

void decryption (char *ifile, char *ofile, char *rfile)
{
    char buf[100000];
    FILE *f;
    int r, err;

    printf("\n");
    printf( "Decrypting\n" );
    printf( "Enter private key file name: " );
    printf("%s\n",rfile );
    
    f = fopen( rfile, "rt" );
    if (f == NULL)
    {
    printf("No such file!\n");
    return;
    } 
    r = fread( buf, 1, sizeof(buf), f );
    fclose(f);

    BIO *publ = BIO_new( BIO_s_mem () );

    err = BIO_write( publ, buf, r );
    if (err == 0)
    {
    show_err( err );
    return;
    } 

    RSA *keypair = PEM_read_bio_RSAPrivateKey( publ, NULL, NULL, NULL );

    printf("\n");
    printf( "Enter encrypted file name: " );

    printf("%s\n", ifile);

    printf("\n");
    printf( "Enter result file name: " );
    printf("%s\n", ofile );
   // fgets(fname2, 1000, stdin);
    //strtok(fname2, "\n");

    if (strcmp(ifile, ofile) == 0)
    {
        printf("Enter another file name!\n");
        return;
    }
    decrypt_file( ifile, ofile, keypair );
}