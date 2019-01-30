#include "ft_printf_internal.h"

static int count_width(ssize_t nb, t_flags *flags)
{
    int nb_len;

    nb_len = nbr_len(nb, flags->base);
    if (nb >= 0 && IS_SET(flags->out_fmt_flags, PLUS))
        nb_len++;
    if (IS_SET(flags->size_flags, WIDTH) && flags->width > nb_len)
        return (flags->width);
    return (nb_len);
}

char *convert_nbr(void *arg, t_flags *flags)
{
    int width;
    char *ret;

    width = count_width(*(ssize_t*)nb, flags);
    ret = (char*)malloc(sizeof(char) * (width + 1));
    return (ret);
}