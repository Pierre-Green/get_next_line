/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:49:24 by pguthaus          #+#    #+#             */
/*   Updated: 2019/11/19 17:41:41 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_buff		*get_initial_buff(void)
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

int					flush_el(t_buff **buff, char **line)
{
	char			eof;

	if (!(*line = malloc(sizeof(char))))
		return (-1);
	(*line)[0] = 0;
	if ((*buff)->len == 0)
	{
		eof = (*buff)->eof;
		clear_buff_next(*buff);
		if (eof)
		{
			*buff = 0;
			return (0);
		}
	}
	else
		trim_buff(*buff, 0);
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
			buff->eol = 1;
			break ;
		}
		i++;
	}
	if (i == buff->len)
		return (0);
	return (1);
}

static int			read_do_buff(t_buff *buff, int fd, char **line, int score)
{
	int				read_ret;
	t_buff			*node;
	char			eol;

	node = buff;
	while (node->len && node->next && node->next->len)
		node = node->next;
	if (node->len)
	{
		if (!(node->next = get_initial_buff()))
			return (-1);
		node = node->next;
	}
	if ((read_ret = read(fd, node->buff, BUFFER_SIZE)) >= 0)
	{
		if (read_ret == 0 && (node->eof = 1))
			return (score);
		score += (node->len = read_ret);
		if ((eol = get_eol(node)) >= 0 && read_ret < BUFFER_SIZE)
			node->eof = 1;
		else if (!eol)
			return ((score = read_do_buff(node, fd, line, score)));
	}
	return (score);
}

int					get_next_line(int fd, char **line)
{
	static t_buff	*buff[(unsigned long)INT_MAX + 1];
	t_buff			*ptr;
	int				read_ret;

	if (read(fd, NULL, 0) < 0 || BUFFER_SIZE == 0 || !line)
		return (-1);
	if ((ptr = buff[fd]))
		while (ptr)
		{
			if ((ptr->buff[0] == '\n' && !ptr->eol && ptr->len)
				|| (ptr->eof && !ptr->len))
				return (flush_el(&(buff[fd]), line));
			else if (ptr->eol || (ptr->eof && ptr->len))
				return (flush_to_eol(&(buff[fd]), line));
			ptr = ptr->next;
		}
	else if (!(buff[fd] = get_initial_buff()))
		return (-1);
	if ((read_ret = read_do_buff(buff[fd], fd, line, 0)) > 0 || buff[fd]->len != 0)
		return (flush_to_eol(&(buff[fd]), line));
	if (read_ret == 0)
		flush_el(&(buff[fd]), line);
	return (read_ret == 0 ? 0 : -1);
}
