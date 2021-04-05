
#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

int main ( int argc, char * argv[] )
{
    int fd;

    fd = open( argv[1], O_WRONLY );     /* Open 1: check if file exists */

    if (fd != -1) {                       /* open succeeded */
        printf( "[PID %ld] File \"%s\" already exists\n", (long) getpid(), argv[1] );
        close( fd );
    }
    else {
        if ( errno != ENONET ) {          /* failed for unexpected reason */
            errExit( "open" );
        }
        else {
            printf( "[PID %ld] File \"%s\" doesn't exist yet\n", (long) getpid(), argv[1] );
            if ( argc > 2 ) {           /* for arbitrary arg[2], it will trigger sleep of the process */
                sleep( 5 );
                printf( "[PID %ld] Done sleeping\n", (long) getpid() );
            }

            fd = open( argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR );
            if ( fd == -1 )
                errExit( "open" );

            printf( "[PID %ld] Created file \"%s\" exclusively\n",      /* MAY NOT BE TRUE */
                    (long) getpid(), argv[1] );
        }
    }

    exit(EXIT_SUCCESS);
}