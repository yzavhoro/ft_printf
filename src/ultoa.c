#include "ft_printf_internal.h"

char str[21];

static int nbr_len(size_t val, int base)
{
    int len;
    
    len = 1;
    while (val /= base)
        len++;
    return len;
}

void ltoa(char *dest, size_t val, int base, int _case)
{
    int len;
    char *nbs;
    
    nbs = (_case == UPPER_CASE ? "0123456789ABCDE" : "0123456789abcde");
    len = nbr_len(val, base);
    while (len--)
    {
        *(dest + len) = nbs[val % base];
        val /= base;
    }
}

int main()
{
    ltoa(str, 18446744073709551615, 10, UPPER_CASE);
    printf("%s\n", str);
    return 0;
}