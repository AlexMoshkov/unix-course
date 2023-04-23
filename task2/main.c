#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>

#define LOCK_FILE_EXTENSION ".lck"

int lock_fd = -1;
char lock_file_name[255];

void stop() {
    close(lock_fd);
    unlink(lock_file_name);
    exit(0);
}

int main(int argc, char **argv) {
    signal(SIGINT, stop);
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *file_name = argv[1];
    sprintf(lock_file_name, "%s%s", file_name, LOCK_FILE_EXTENSION);

    char spid[20];
    sprintf(spid, "%d", getpid());

    while (true) {
        while (lock_fd == -1) { lock_fd = open(lock_file_name, O_CREAT | O_EXCL | O_WRONLY, 0500); }

        ssize_t written = write(fd, spid, strlen(spid));
        if (written == -1) {
            perror("Couldn't write pid to lock file");
            close(fd);
            return EXIT_FAILURE;
        }

        sleep(1);
        printf("%s\n", spid);

        close(lock_fd);
        unlink(lock_file_name);
    }
}
