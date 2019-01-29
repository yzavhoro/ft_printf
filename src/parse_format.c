#include "ft_printf_internal.h"
#include <stdarg.h>

static void fill_size_flags(char **fmt, t_flags *flags)
{
    
}

static void fill_width_prec(char **fmt, t_flags *flags)
{
    if (isdigit(**fmt))
    {
        SET_FLAG(flags->out_fmt_flags, WIDTH);
        flags->width = atoi(*fmt);
        *fmt += nbr_len(flags->width, 10);
    }
    if (**fmt == '.')
    {
        SET_FLAG(flags->out_fmt_flags, PRECISION);
        (*fmt)++;
        flags->precision = atoi(*fmt);
        while (isdigit(**fmt))
            (*fmt)++;
    }
}

static void fill_flags(char **fmt, t_flags *flags)
{
    static char *out_fmt_flags = "*#0-+ ";
    int i;

    while (**fmt)
    {
        i = 0;
        while (i < MAX_FMT_FLAG)
        {
            if (**fmt == out_fmt_flags[i])
            {
                SET_FLAG(flags->out_fmt_flags, i);
                break;
            }
            i++;
        }
        if (i == MAX_FMT_FLAG)
            break;
        (*fmt)++;
    }
}

void parse_format(char **fmt, t_flags *flags)
{
    bzero(flags, sizeof(t_flags));
    fill_out_fmt_flags(fmt, flags);
    fill_width_prec(fmt, flags);
    fill_size_flags(fmt, flags);
}