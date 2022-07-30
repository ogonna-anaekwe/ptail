#include "ptail.h"

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        fprintf(stderr, "usage: ./ptail <file_path> <optional: num_of_lines_to_print>\n");
        exit(1);
    }

    char *file_path = argv[1];
    ssize_t num_of_lines = argc == 2 ? DEFAULT : strtol(argv[2], NULL, INPUT_BASE) - 1;

    ptail(file_path, num_of_lines);
    return 0;
}