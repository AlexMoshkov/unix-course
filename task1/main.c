#include <getopt.h>
#include "sparse.c"

#define DEFAULT_BLOCK_SIZE 4096

const char* USAGE_MESSAGE = "Usage: %s [-b/--block-size <size>] [<input_file>] <output_file>\n";

void parse_arguments(int argc, char **argv, int* block_size, char** input_filename, char** output_filename) {
    const struct option long_options[] = {
            {"block-size", required_argument, NULL, 'b'},
            {NULL, 0, NULL, 0},
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "b:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'b':
                *block_size = atoi(optarg);
                if (*block_size <= 0) {
                    fprintf(stderr, "block size must be > 0, got %d\n", *block_size);
                    exit(1);
                }
                break;
            default:
                fprintf(stderr, USAGE_MESSAGE, argv[0]);
                exit(1);
        }
    }

    if (optind == argc - 1) {
        *input_filename = "/dev/stdin";
        *output_filename = argv[optind];
    } else if (optind == argc - 2) {
        *input_filename = argv[optind];
        *output_filename = argv[optind + 1];
    } else {
        fprintf(stderr, USAGE_MESSAGE, argv[0]);
        exit(1);
    }
}

int main(int argc, char **argv) {
    int block_size = DEFAULT_BLOCK_SIZE;
    char* input_filename;
    char* output_filename;

    parse_arguments(argc, argv, &block_size, &input_filename, &output_filename);

    sparse_file(input_filename, output_filename, block_size);

    return 0;
}
