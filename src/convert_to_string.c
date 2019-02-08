#include "ft_printf_internal.h"
#include <stdarg.h>

char*(*f)(void *, t_flags *) g_convert_funcs[] = {
    convert_char,
    convert_string,
    convert_uni_char,
    convert_uni_str,
    convert_nbr,
    convert_unsg_nbr,
};

static void set_base(char type, t_flags *flags)
{
    if (strchr("diu", type))
        flags->base = DEC;
    else if (strchr("xX", type))
        flags->base = HEX;
    else if (strchr("oO", type))
        flags->base = OCT;
    else if (type == 'b')
        flags->base = BIN;
    if (type == 'X')
        SET_FLAG(flags->out_fmt_flags, UPPERCASE);
}

static int choose_converter(char type, t_flags *flags)
{
    static char *specifiers = SPECIFIERS;
    static int  thresholds[] = {0, 1, 2, 3, 5, 10, 11}; //TODO try to find a better way to do that
    int         i;
    int         j;

    i = 0;
    while (type != specifiers[i])
        i++;
    if (i > thresholds[UNI_STRING])
        set_base(type, flags);
    j = -1;
    while (j < MAX_CONV_TYPE)
    {
        j++;
        if (i <= threshold[j])
            break;
    }
    return (j);
}

static int case_pointer(t_flags * flags)
{
    SET_FLAG(flags->out_fmt_flags, HASH);
    flags->base = HEX;
    UNSET_FLAG(flags->out_fmt_flags, UPPERCASE);
    return (UNSG_NUMBER);
}

char *convert_to_string(char **fmt, va_list lst)
{
    t_flags flags;
    int     i;
    void    *arg;

    parse_format(fmt, &flags);
    i = choose_converter(**fmt, &flags);
    if (i == MAX_CONV_TYPE)
    {
        arg = (void*)(*fmt);
        i = CHAR;
    }
    else
    {
        arg = va_arg(lst, void*);
        if (i >= NUMBER)
        {
            if (i < POINTER && !IS_LONG(flags.size_flags)))
               CLEANUP(arg);
            if (i == POINTER)
                i = case_pointer(&flags);
            else
                set_base(**fmt, &flags);
        }
    }
    (*fmt)++;
    return (g_convert_funcs[i](arg, &flags));
}