#include "utils.h"

char* key_to_str( BIO *key )
{
    int l = BIO_pending(key);
    char *s = (char*) malloc(l + 1);

    BIO_read( key, s, l );
    s[l] = 0;

    return s;
}

int fsize( FILE *f )
{
    fseek( f, 0, SEEK_END );
    int r =  ftell( f );

    return r;
}

void show_err( int err )
{
    char s[1000];

    ERR_load_crypto_strings();
    ERR_error_string(ERR_get_error(), s);

    printf("Error message: %s\n", s);
}
