#include "ft_printf_internal.h"
#include <stdarg.h>

#define CONV_SPEC '%'

static int	parse_format(const char *fmt, va_list arg)
{
	char	*word;
	t_chunk	*chunk;
	int	len;

	chunk = NULL;
	while (fmt)
	{
		if (*fmt != CONV_SPEC)
		{
			word = ft_strndup(fmt, ft_strchr(fmt, CONV_SPEC) - fmt);
			fmt = ft_strchr(CONV_SPEC);
		}
		else
		{
			word = convert_to_string(&fmt, arg);
		}
		join_chunk(&chunk, word);
	}
	
}
//TODO list of strings with size only at the beginning
int	printf(const char *format, ...)
{
	va_list arg;
	int printed;

	va_start(arg, format);
	printed = parse_format(format, arg);
	va_end(arg);
	return (printed);
}
