/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:49:24 by pguthaus          #+#    #+#             */
/*   Updated: 2019/11/05 19:38:52 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_buff		*get_initial_buff()
{
	t_buff			*buff;

	if (!(buff = malloc(sizeof(t_buff))))
		return (NULL);
	buff->eol = 0;
	buff->eof = 0;
	buff->len = 0;
	buff->next = NULL;
	return (buff);
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


static int		read_do_buff(t_buff *buff, int fd, char **line)
{
	int			read_ret;
	t_buff		*node;

	node = buff;
	while (node->len && node->next && node->next->len)
		node = node->next;
	if (node->len)
	{
		if (!(node->next = get_initial_buff()))
			return (-1);
		node = node->next;
	}
	if ((read_ret = read(fd, node->buff, BUFF_SIZE)) >= 0)
	{
		if (read_ret == 0)
			return (0);
		node->len = read_ret;
		if (read_ret < BUFF_SIZE)
			node->eof = 1;
		if (!get_eol(node))
			return (read_do_buff(node, fd, line));
	}
	return (read_ret);
}

int					get_next_line(int fd, char **line)
{
	static t_buff	*buff;
	char			tmp[1];
	t_buff			*ptr;
	int				read_ret;

	if ((ptr = buff))
		while (ptr)
		{
			if (ptr->eol || ptr->eof || ptr->buff[0] == '\n')
				return (flush_to_eol(&buff, line));
			ptr = ptr->next;
		}
	else if (!(buff = get_initial_buff()))
		return (-1);
	if (read(fd, tmp, 0) < 0)
		return (-1);
	if ((read_ret = read_do_buff(buff, fd, line)) >= 0)
		return (flush_to_eol(&buff, line));
	return (-1);
}
