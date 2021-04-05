
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

extern int optind, opterr, optopt;
extern char *optarg;


#define printable(ch) ( isprint((unsigned char)ch)? ch : '?' )


int main ( int argc, char * argv[] )
{
    int opt, ofd, do_append, i, nopt, oflags;
    mode_t perms_flags;
    ssize_t rsz;
    char buf[64];

    // check stdin buffer is not empty
    if ( lseek(STDIN_FILENO, 0, SEEK_END) <= 0 )
        return 0;   // no input, nothing to do

    nopt = do_append = 0;

    while ( (opt = getopt(argc, argv, ":a")) != -1 ) {
        //printf("opt =%3d (%c); optind = %d\n", opt, printable(opt), optind);

        if (opt == 'a')
            do_append = 1;

        nopt += 1;
    }

    // output to file
    oflags = O_WRONLY | O_CREAT | (do_append ? O_APPEND : 0 );
    perms_flags = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;  /* rw-rw-r-- */

    for (i = 1 + nopt; i < argc; ++i) {

        ofd = open(argv[i], oflags, perms_flags);
        if (ofd == -1)
            continue;   // failed to open file, proceed to next file

        lseek(STDIN_FILENO, 0, SEEK_SET);
        while ((rsz = read(STDIN_FILENO, buf, sizeof(buf))) > 0 ) {
            write(ofd, buf, rsz);
        }

        close(ofd);
    }

    // output to stdout
    lseek(STDIN_FILENO, 0, SEEK_SET);
    while ((rsz = read(STDIN_FILENO, buf, sizeof(buf))) > 0 ) {
        write(STDOUT_FILENO, buf, rsz);
    }
}