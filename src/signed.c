#include "ft_printf_internal.h"
#define PLUS 4
#define WDTH 4
#define PRES 5

static int count_width(ssize_t nb, t_flags *flags)
{
    int nb_len;

    nb_len = nbr_len(nb, flags->base);
    if (nb > 0 && IS_SET(flags->out_fmt_flags, PLUS)) //TODO check if +0 output is possible
        nb_len++;
    if (IS_SET(flags->size_flags, WDTH) && flags->width > nb_len)
        return (flags->width);
    return (nb_len);
}

void bufferize_signed(ssize_t nb, t_flags *flags)
{
    int width;

}