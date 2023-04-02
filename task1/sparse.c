#include <stdbool.h>
#include "safe.c"

bool check_zero_block(const char* block, long read_count) {
    for (int i = 0; i < read_count; ++i)
        if (block[i] != 0)
            return false;
    return true;
}

void sparse_file(const char* input_filename, const char* output_filename, int block_size) {
    int input = safe_open(input_filename, O_RDONLY, 0, "Error while open input file");
    int output = safe_open(output_filename, O_WRONLY | O_CREAT, 0666,
                           "Error while open output file");

    char* buf = malloc(block_size);
    size_t output_len = 0;
    long read_count;
    while ((read_count = safe_read(input, buf, block_size, "Error while read file")) != 0) {
        output_len += read_count;
        if (check_zero_block(buf, read_count))
            safe_lseek(output, read_count, SEEK_CUR, "Error while seek file");
        else
            safe_write(output, buf, read_count, "Error while write file");
    }

    safe_ftruncate(output, (long)output_len, "Error while truncate file");

    safe_close(input, "Error while close input file");
    safe_close(output, "Error while close output file");
}
