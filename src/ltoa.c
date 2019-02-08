#include "ft_printf_internal.h"
#include <string.h>
char str[21];

int nbr_len(size_t val, int base)
{
    int len;

    len = 1;
    while ((val /= base))
        len++;
    return len;
}

void ltoa(char *dest, ssize_t val, int base, int _case)
{
    int len;
    char *nbs;
    
    nbs = (_case == UPPER_CASE ? "0123456789ABCDE" : "0123456789abcde");
    if (val == MIN_LONG && base == 10)
    {
        strcpy(dest, "-9223372036854775808");
        return ;
    }
    if (val < 0)
    {
        *dest++ = '-';
        val *= -1;
    }
    len = nbr_len(val, base);
    while (len--)
    {
        *(dest + len) = nbs[val % base];
        val /= base;
    }
}