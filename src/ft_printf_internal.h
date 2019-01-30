#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include <unistd.h>

# define SPECIFIERS "csCSdiouxXbp" //TODO handle float/double
# define MIN_LONG -9223372036854775807 -1

# define LOWER_CASE 0
# define UPPER_CASE 1

#define IS_SET(flags, n) (((flags) >> (n)) & 1)
#define SET_FLAG(flags, n) ((flags) |= (1 << (n)))
#define UNSET_FLAG(flags, n) ((flags) &= ~(1 << (n)))

enum e_size_flags {
	LONG_LONG,
	SHORT_SHORT,
	LONG,
	SHORT,
	INTMAX_T,
	SIZE_T,

	SIZE_FLAG_MAX,
};

enum e_out_fmt_flags {
	HASH,
	ZERO,
	MINUS,
	PLUS,
	SPACE,

	MAX_FMT_FLAG,

	WIDTH = MAX_FMT_FLAG,
	PRECISION,
}

enum e_conv_types {
	CHAR,
	STRING,
	UNI_CHAR,
	UNI_STRING,
	NUMBER,
	UNSG_NUMBER,

	MAX_CONV_TYPE,
};

typedef struct		s_chunk {
	char			*word;
	int				len;
	struct s_chunk	*next;
}					t_chunk;

typedef struct		s_output {
	t_chunk			*head;
	t_chunk			*tail;
	int				total_len;
}					t_output;

typedef struct		s_flags {
	int				width;
	int				precision;
	char			size_flags; /* l ll h hh j z */
	char			out_fmt_flags; /* # 0 - + space w p*/
	int				base;
}					t_flags;

char *convert_char(void *arg, t_flags *flags);
char *convert_string(void *arg, t_flags *flags);
char *convert_uni_char(void *arg, t_flags *flags);
char *convert_uni_str(void *arg, t_flags *flags);
char *convert_nbr(void *arg, t_flags *flags);
char *convert_unsg_nbr(void *arg, t_flags *flags);

// extern char*(*f)(void *, t_flags *) g_convert_funcs[MAX_CONV_TYPE];

#endif
