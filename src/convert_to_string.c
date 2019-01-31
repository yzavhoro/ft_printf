#include "ft_printf_internal.h"
#include <stdarg.h>

char*(*f)(void *, t_flags *) g_convert_funcs[] = {
    convert_char,
    convert_string,
    convert_uni_char,
    convert_uni_str,
    convert_nbr,
    convert_unsg_nbr,
}

static int choose_converter(char type, t_flags *flags)
{
    static char *specifiers = SPECIFIERS;
    static int  *thresholds = {0, 1, 2, 3, 5, 11}; //TODO try to find a better way to do that
    int         i;
    int         j;

    i = 0;
    while (type != specifiers[i])
        i++;
    j = 0;
    while (j < MAX_CONV_TYPE)
    {
        if (i <= threshold[j])
            break;
        j++;
    }
    return (j);
}

char *convert_to_string(char **fmt, va_list arg)
{
    t_flags flags;
    int     i;

    parse_format(fmt, &flags);
    i = choose_converter(**fmt, &flags);
    if (i == MAX_CONV_TYPE)
        return (g_convert_funcs[CHAR]((void*)(*fmt++), &flags));
    *fmt++;
    return (g_convert_funcs[i](va_arg(arg, void*), &flags));
}