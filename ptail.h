#ifndef __ptail_h__
#define __ptail_h__

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Struct for the list of lines (in a file).
This is a doubly linked list.
*/
struct node
{
    struct node *prev_line;
    char *line;
    struct node *next_line;
};

#define CHECK_MALLOC(ptr) assert(ptr != NULL); /* Checks that valid ptr (i.e. non-null) is returned. */

#define CHECK_FILE(ptr, file_path)                             \
    if (ptr == NULL)                                           \
    {                                                          \
        fprintf(stderr, "ptail: cannot open %s\n", file_path); \
        exit(1);                                               \
    }; /* Checks that file path is valid and returns a valid file stream. */

#define CHECK_REQUEST(is_invalid, file_path, file_line_count, lines_to_print)                                                                                                             \
    if (is_invalid)                                                                                                                                                                       \
    {                                                                                                                                                                                     \
        fprintf(stderr, "\"%s\" has %zd lines.\nSpecify that number (or less) and re-try.\nYou specified (or are using the default) %zd.\n", file_path, file_line_count, lines_to_print); \
        exit(1);                                                                                                                                                                          \
    }; /* Checks that user isn't asking to print more lines than the file has. */

#define DEFAULT 5 /* Number of lines to print (if the user doesn't specify the number of lines to print) */
#define INPUT_BASE 10

/**
 * Prints the tail of a file. Say a file has 10 lines and you want to print the tail,
 * we print the last 5 lines (i.e lines 6 to 10) by default. You can bypass this by passing the number of lines
 * you'd rather have printed.
 * @param file_path Path to file whose tail we want to print.
 * @param lines_to_print Number of lines to be printed. Default: 5.
 */
void ptail(const char *file_path, long lines_to_print);

#endif //__ptail_h__