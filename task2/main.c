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
        lock_fd = -1;
        while (lock_fd == -1) { lock_fd = open(lock_file_name, O_CREAT | O_EXCL | O_WRONLY, 0500); }

        ssize_t written = write(lock_fd, spid, strlen(spid));
        if (written < 0) {
            perror("Couldn't write pid to lock file");
            close(lock_fd);
            return EXIT_FAILURE;
        }

        sleep(1);
        printf("%s\n", spid);


        int fd = open(lock_file_name, O_RDONLY);
        if (fd < 0) {
            perror("Error while open lock file");
            return EXIT_FAILURE;
        }

        char buf[20];
        ssize_t read_count = read(fd, buf, 20);
        if (read_count < 0) {
            perror("Error while read lock file");
            return EXIT_FAILURE;
        }
        if (strcmp(buf, spid) != 0) {
            fprintf(stderr, "Lock file is corrupted, pid must be %s\n", spid);
            return EXIT_FAILURE;
        }

        close(lock_fd);
        unlink(lock_file_name);
    }
}
