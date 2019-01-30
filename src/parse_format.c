#include "ft_printf_internal.h"

static void handle_overlaps(char *o_fmt_fl)
{
    if (IS_SET(*o_fmt_fl, MINUS) || IS_SET(*o_fmt_fl, PRECISION))
        UNSET_FLAG(*o_fmt_fl, ZERO);
    if (IS_SET(*o_fmt_fl, PLUS))
        UNSET_FLAG(*o_fmt_fl, SPACE);
}

static void fill_size_flags(char **fmt, t_flags *flags)
{
    static char *size_flags = "lhjz";
    int i;

    if (!strncmp(*fmt, "ll", 2))
        SET_FLAG(flags->size_flags, LONG_LONG);
    else if (!strncmp(*fmt, "hh", 2))
        SET_FLAG(flags->size_flags, SHORT_SHORT);
    i = LONG;
    while (i < SIZE_FLAG_MAX)
    {
        if (*fmt == size_flags[i])
            SET_FLAG(flags->size_flags, i);
        i++;
    }
}

static void fill_width_pres(char **fmt, t_flags *flags)
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
    fill_width_pres(fmt, flags);
    fill_size_flags(fmt, flags);
    handle_overlap(&(flags->out_fmt_flags));
}