
#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"


int main ( int argc, char *argv[] )
{
    int fd;
    size_t len;
    ssize_t wsz;
    off_t off;

    if ( argc != 3 || strcmp(argv[1], "--help") == 0 )
        usageErr( "%s file append_string\n", argv[0] );

    if ( (fd = open(argv[1], O_WRONLY | O_APPEND)) == -1 )
        errExitEN( errno, "failed to open file: %s", argv[1] );

    off = lseek( fd, 0, SEEK_SET );
    if ( off == -1 )
        errExitEN( errno, "failed to seek to beginning of file: %s", argv[1] );

    len = strlen(argv[2]);
    wsz = write( fd, argv[2], len );
    if (wsz == -1)
        errExitEN(errno, "write() return %ld\n", wsz);

    close( fd );

    exit(EXIT_SUCCESS);
}