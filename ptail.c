#include "ptail.h"

void ptail(const char *file_path, long lines_to_print)
{
    char *mode = "r",
         *line_ptr = NULL;
    FILE *fp = fopen(file_path, mode);
    CHECK_FILE(fp, file_path);

    bool invalid_line_requested = 0; /* Checks if user's asked to print more lines than are contained in the file */

    size_t line_cap = 0;
    ssize_t line_len,
        file_line_count = 0; /* # of lines in file which must (eventually) match the number of nodes in the list */

    struct node *head = NULL,
                *tail = NULL,
                *list = NULL,
                *temp_list = NULL,
                *new_node;

    while ((line_len = getline(&line_ptr, &line_cap, fp)) != -1)
    {
        new_node = (struct node *)malloc(sizeof(struct node));
        CHECK_MALLOC(new_node);

        if (list != NULL)
        {
            new_node->next_line = list; /* Link new node to list. This is the pointer to the next node. */
            list->prev_line = new_node; /* Link list node. This is the pointer to the previous node. */
            new_node->prev_line = head;
        }
        else
        {
            new_node->next_line = tail; /* This is executed only for the first node added to the list */
        }

        new_node->line = (char *)malloc(line_cap); /* Why does line_len cause seg fault if passed here? */
        CHECK_MALLOC(new_node->line);
        strncpy(new_node->line, line_ptr, line_len);

        list = new_node;

        file_line_count++;
    }

    invalid_line_requested = lines_to_print > file_line_count; /* Asking to print more lines than are in the file */
    CHECK_REQUEST(invalid_line_requested, file_path, file_line_count, lines_to_print);

    while (list)
    {
        /* The list holds lines from the file backwards
         * i.e. the first line is the last node and the last line is the first node.
         * So starting from the first node (i.e. the last line), we step through
         * the list lines_to_print times. And then starting from that point,
         * we repeatedly print the previous node until we reach the first node (i.e. the last line).
         */
        if (lines_to_print == 1)
        {
            temp_list = list;
            while (temp_list)
            {
                printf("%s", temp_list->line);
                temp_list = temp_list->prev_line;
            }
            break;
        }
        list = list->next_line;
        lines_to_print--; /* Decrement each time we step through the list. This will eventually help set the list to the point from which we can start printing the prev_line's line */
    }

    free(list); /* All mallocs were re-assigned to this node. Only this needs freeing as the original mallocs were freed upon re-assignment */
    printf("\n");
}