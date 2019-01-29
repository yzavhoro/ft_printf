#include "ft_printf_internal.h"

static void     list_del_one(t_chunk **chunk)
{
    free((*chunk)->word);
    free(*chunk);
}

void            list_del(t_chunk **head) {
    t_chunk *del;
    t_chunk *next;

    if (!head || !(*head))
        return;
    del = *head;
    while (del)
    {
        next = del->next;
        list_del_one(&del);
        del = next;
    }
}

static void     join_to_list(t_output *out, t_chunk *chunk)
{
    if (!out || !chunk)
        return;
    if (!out->head)
        out->head = chunk;
    else
        out->tail->next = chunk;
    out->tail = chunk;
}

void            join_chunk(t_output *output, char *word)
{
    t_chunk *new_chunk;

    new_chunk = (t_chunk*)calloc(sizeof(t_chunk));
    new_chunk->word = word;
    new_chunk->len = strlen(word);
    join_to_list(output, new_chunk);
}