#include "ft_printf_internal.h"

//TODO still need to count strlen of each chunk so

char *ft_strjoin_list(t_output *output)
{
	t_chunk	*tmp;
	char	*str;
	int		printed;

	if (!output)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(char) * output->total_len)))
		return (NULL);
	tmp = output->head;
	printed = 0;
	while (tmp)
	{
		strncpy(str + printed, tmp->word, tmp->len);
		printed += tmp->len;
		tmp = tmp->next;
	}
	str[printed] = '\0';
	return (str);
}
