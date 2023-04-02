#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int safe_open(const char* filename, int flags, mode_t mode, const char* err_msg) {
    int fd = open(filename, flags, mode);
    if (fd < 0) {
        perror(err_msg);
        exit(2);
    }
    return fd;
}

ssize_t safe_read(int fd, void* buf, size_t nbytes, const char* err_msg) {
    ssize_t read_count = read(fd, buf, nbytes);
    if (read_count < 0) {
        perror(err_msg);
        exit(3);
    }
    return read_count;
}

long safe_lseek(int fd, int offset, int whence, const char* err_msg) {
    long res = lseek(fd, offset, whence);
    if (res < 0) {
        perror(err_msg);
        exit(4);
    }
    return res;
}

long safe_write(int fd, void* buf, int n, const char* err_msg) {
    long res = write(fd, buf, n);
    if (res < 0) {
        perror(err_msg);
        exit(5);
    }
    return res;
}

int safe_ftruncate(int fd, long length, const char* err_msg) {
    int res = ftruncate(fd, length);
    if (res < 0) {
        perror(err_msg);
        exit(6);
    }
    return res;
}

int safe_close(int fd, const char* err_msg) {
    int res = close(fd);
    if (res < 0) {
        perror(err_msg);
        exit(7);
    }
    return res;
}