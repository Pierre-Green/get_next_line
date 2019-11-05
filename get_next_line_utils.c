/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 16:09:13 by pguthaus          #+#    #+#             */
/*   Updated: 2019/11/05 20:32:55 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t			len_to_eol(t_buff *buff)
{
	t_buff		*node;
	size_t		len;

	node = buff;
	len = 0;
	while (node->next && !node->eol && node->buff[0] != '\n')
	{
		len += node->len;
		node = node->next;
	}
	if (node->eol)
		len += node->eol;
	else if (!node->next && node->buff[0] != '\n')
		len += node->len;
	return (len);
}

static void			trim_buff(t_buff *buff)
{
	char			tmp[BUFF_SIZE];
	unsigned int	i;
	unsigned int	j;
	char			lock;

	i = buff->eol + 1;
	buff->eol = 0;
	lock = 0;
	j = 0;
	while (j < buff->len - i)
	{
		if (!lock && buff->buff[i + j] == '\n' && (lock = 1))
			buff->eol = j;
		tmp[j] = buff->buff[i + j];
		j++;
	}
	i = 0;
	buff->len = j;
	while (i < buff->len)
	{
		buff->buff[i] = tmp[i];
		i++;
	}
}

static t_buff		*clear_buff_next(t_buff *buff)
{
	t_buff			*ptr;

	ptr = buff->next;
	free((void *)buff);
	return (ptr);
}

int					flush_to_eol(t_buff **buff, char **line)
{
	const size_t	len = len_to_eol(*buff);
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	if (!(*line = malloc(sizeof(char) * (len + 1))))
		return (-1);
	(*line)[len] = 0;
	i = 0;
	if (len == 0)
		trim_buff(*buff);
	while (i < len)
	{
		j = 0;
		while (j < (*buff)->len && (*buff)->buff[j] != '\n')
		{
			(*line)[i + j] = (*buff)->buff[j];
			j++;
		}
		if ((*buff)->buff[j] == '\n')
			trim_buff(*buff);
		else
			*buff = clear_buff_next(*buff);
		i += j;
	}
	if ((*buff)->buff[0] == '\n')
		*buff = clear_buff_next(*buff);
	return (1);
}
