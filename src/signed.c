#include "ft_printf_internal.h"

typedef struct  s_additional_params {
    int width;
    int pres;
    int add_symb;
    int nb_len;
    int str_len;
}               t_additional_params;

static void precount(t_additional_params *ap, ssize_t nb, t_flags *flags)
{
    bzero(ap, sizeof(t_additional_params));
    if (nb < 0)
    {
        UNSET_FLAG(flags->out_fmt_flags, PLUS);
        UNSET_FLAG(flags->out_fmt_flags, SPACE);
    }
    ap->add_symb = IS_SET(flags->out_fmt_flags, PLUS) || IS_SET(flags->out_fmt_flags, SPACE);
    ap->nb_len = nbr_len(nb, DEC);
    ap->pres = flags->precision - ap->nb_len;
    CHECK_UNDERFLOW(ap->pres);
    ap->width = flags->width - (ap->nb_len + ap->add_symb + ap->pres);
    CHECK_UNDERFLOW(ap->width);
    ap->str_len = ap->nb_len + ap->add_symb + ap->pres + ap->width;
}

static int count_offset(t_additional_params *ap, t_flags *flags)
{
    int offset;

    offset = ap->add_symb + ap->pres;
    if (!IS_SET(flags->out_fmt_flags, MINUS))
        offset += ap->width;
    return (offset);
}

static void fill_str(char *str, t_additional_params *ap, ssize_t nb, t_flags *flags)
{
    int offset;
    int wdth_off;

    offset = count_offset(ap, flags);
    ltoa(str + offset, nb, DEC, ANY);
    if (ap->add_symb)
        *(str + offset - ap->pres - 1) = IS_SET(flags->out_fmt_flags, PLUS) ? '+' : ' ';
    if (ap->pres)
        memset((void*)(str + offset - ap->pres), '0', ap->pres);
    if (ap->width)
    {
        wdth_off = IS_SET(flags->out_fmt_flags, MINUS) * (ap->str_len - ap->width);
        memset((void*)(str + wdth_off),
            IS_SET(flags->out_fmt_flags, ZERO) ? '0' : ' ', ap->width);
    }
}

char *convert_nbr(void *arg, t_flags *flags)
{
    t_additional_params ap;
    char                *ret;
    ssize_t             nb;

    nb = *(ssize_t*)arg;
    precount(&ap, nb, flags);
    ret = (char*)malloc(sizeof(char) * (ap.str_len + 1));
    ret[ap.str_len] = 0;
    fill_str(ret, &ap, nb, flags);
    return (ret);
}
