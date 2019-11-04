/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 16:09:13 by pguthaus          #+#    #+#             */
/*   Updated: 2019/11/04 19:09:59 by pguthaus         ###   ########.fr       */
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
		i += j;
		if (i < len)
			*buff = (*buff)->next;
	}
	return (1);
}

static char			get_eol(t_buff *buff)
{
	unsigned int	i;

	i = 0;
	while (i < buff->len)
	{
		if (buff->buff[i] == '\n')
		{
			buff->eol = i;
			break ;
		}
		i++;
	}
	if (i == buff->len)
		return (0);
	return (1);
}

int				read_do_buff(t_buff *buff, int fd, char **line)
{
	int			read_ret;
	t_buff		*node;

	node = buff;
	while (node->len && node->next && node->next->len)
		node = node->next;
	if (node->len)
	{
		if (!(node->next = malloc(sizeof(t_buff))))
			return (-1);
		node->next->eol = 0;
		node->next->len = 0;
		node->next->next = 0;
		node = node->next;
	}
	if ((read_ret = read(fd, node->buff, BUFF_SIZE)) >= 0)
	{
		if (read_ret == 0)
			return (0);
		node->len = read_ret;
		if (!get_eol(node))
			return (read_do_buff(node, fd, line));
	}
	return (-1);
}
