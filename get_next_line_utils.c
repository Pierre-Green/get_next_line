/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 16:09:13 by pguthaus          #+#    #+#             */
/*   Updated: 2019/11/07 15:21:54 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t				len_to_eol(t_buff *buff)
{
	t_buff			*node;
	size_t			len;
	size_t			i;

	node = buff;
	len = 0;
	while (node->next && !node->eol && (len += node->len))
		node = node->next;
	if (node->eol)
	{
		i = 0;
		while (i < node->len)
		{
			if (node->buff[i] == '\n')
			{
				len += i;
				break ;
			}
			i++;
		}
	}
	else if (!node->next)
		len += node->len;
	return (len);
}

void				trim_buff(t_buff *buff, unsigned int nl)
{
	char			tmp[BUFF_SIZE];
	unsigned int	i;
	unsigned int	j;

	i = nl + 1;
	buff->eol = 0;
	j = 0;
	while (j < buff->len - i)
	{
		if (j > 0 && buff->buff[i + j] == '\n')
			buff->eol = 1;
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

t_buff				*clear_buff_next(t_buff *buff)
{
	t_buff			*ptr;

	ptr = buff->next;
	free((void *)buff);
	return (ptr);
}

static size_t		do_buff(t_buff **buff, char **line, unsigned int i)
{
	size_t			j;

	j = 0;
	while (j < (*buff)->len && (*buff)->buff[j] != '\n')
	{
		(*line)[i + j] = (*buff)->buff[j];
		j++;
	}
	if ((*buff)->buff[j] == '\n' && j < (*buff)->len)
		trim_buff(*buff, j);
	else
		*buff = clear_buff_next(*buff);
	return (j);
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
		trim_buff(*buff, 0);
	while (i < len)
		i += do_buff(buff, line, i);
	if ((*buff)->buff[0] == '\n' && (*buff)->eol && (*buff)->len)
		trim_buff(*buff, 0);
	return ((*buff)->len == 0 && (*buff)->eof ? 0 : 1);
}
