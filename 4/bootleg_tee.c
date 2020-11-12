/* This is a bootleg implementation of tee written to satisfy exercise 4-1
 * in Linux Programming Interface.
 * */

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../tlpi-dist/lib/tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int
main(int argc, char *argv[])
{
    int outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buffer[BUF_SIZE];

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    outputFd = open(argv[1], openFlags, filePerms);
    if (outputFd == -1)
        exit(1);

    // Read data from stdin unil EOF
    // It's pretty much the same as copying from any file handle
    while ((numRead = read(STDIN_FILENO, buffer, BUF_SIZE)) > 0)
        if (write(outputFd, buffer, numRead) != numRead)
            exit(1);
    if (numRead == -1)
        exit(1);

    // Clean up fd
    if (close(outputFd) == -1)
        exit(1);

    exit(EXIT_SUCCESS);
}