#include "encryption.h"
#include "utils.h"

void encrypt_file( char *in_name, char *out_name, RSA *keypair )
{
    FILE *in = fopen( in_name, "rb" );
    FILE *out = fopen( out_name, "wb" );

    int l = RSA_size(keypair), r, r2;

    byte *in_buf = (byte*) malloc( l + 1 );
    byte *encrypt = (byte*) malloc( l );

    while (!feof(in))
    {
        memset( in_buf, 0, l );

        r = fread( in_buf, 1, l, in );

        r2 = RSA_public_encrypt( r, in_buf, encrypt, keypair, RSA_PKCS1_OAEP_PADDING );

        if (r2 == -1)
        {
            show_err(r2);
            return;
        }

        fwrite( encrypt, 1, r2, out );

        printf( "  encr: %d/%d\n", r, r2 );
    }

    fclose(in);
    fclose(out);
}

void encryption (char *ifile, char *ofile, char *pfile)
{
    char buf[100000];
    FILE *f;
    int r, err;

    printf("\n");
    printf( "Encrypting\n" );
    printf( "Enter public key (file name): " );
    printf("%s\n",pfile);
   
    f = fopen( pfile, "rt" );
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

    RSA *keypair = PEM_read_bio_RSAPublicKey( publ, NULL, NULL, NULL );

    printf("\n");
    printf( "Enter initial file name: " );
    
    //fgets(ifile, 1000, stdin);
    printf("%s\n",ifile);
    printf( "Enter encrypted file name: " );
    
    printf("%s\n",ofile);
    if (strcmp(ofile, ifile) == 0)
    {
        printf("Enter another file name!\n");
        return;
    }

    encrypt_file( ifile, ofile, keypair );
}
