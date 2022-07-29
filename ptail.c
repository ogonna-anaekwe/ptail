#include "ptail.h"

void ptail(const char *file_path, long lines_to_print)
{
    char *mode = "r";
    FILE *fp = fopen(file_path, mode);
    CHECK_FILE(fp);

    char *line_ptr = NULL;

    size_t line_cap = 0;

    ssize_t line_len,
        file_line_count = 0; /* # of lines in file which must (eventually) match the number of nodes in the list */

    struct node *existing_node = NULL,
                *new_node;

    while ((line_len = getline(&line_ptr, &line_cap, fp)) != -1)
    {
        new_node = (struct node *)malloc(sizeof(struct node));
        CHECK_MALLOC(new_node);

        new_node->line = (char *)malloc(line_cap); /* Why does line_len cause seg fault if passed here? */
        CHECK_MALLOC(new_node->line);
        strncpy(new_node->line, line_ptr, line_len);

        new_node->next_line = existing_node;

        existing_node = new_node;

        file_line_count++;
    }

    bool invalid_line_requested = 0;
    invalid_line_requested = lines_to_print >= file_line_count; /* Asking to print more lines than are in the file */
    CHECK_REQUEST(invalid_line_requested);

    while (lines_to_print >= 0)
    {
        printf("%s", (existing_node - (lines_to_print))->line);
        lines_to_print--;
    }

    free(existing_node); /* All mallocs were re-assigned to this node. Only this needs freeing as the original mallocs were freed upon re-assignment */
    printf("\n");
}