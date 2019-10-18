/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:49:24 by pguthaus          #+#    #+#             */
/*   Updated: 2019/10/18 18:19:07 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					get_next_line(int fd, char **line)
{
	static t_buff	*buff;
	char			tmp_buff[BUFF_SIZE];
	int				i;
	int				j;
	t_buff			*node;

	if (!buff)
		if (!(buff = init_buff()))
			return (-1);
	if (read(fd, buff->buff, 0) < 0)
		return (-2);
	node = buff;
	while ((i = read(fd, tmp_buff, BUFF_SIZE)))
	{
		if (i < 0)
			return (buff_clear(buff) ? -3 : -2);
		if ((j = buff_write(node, tmp_buff, i)) < 0)
			return (buff_clear(buff) ? -4 : -5);
		if (j < i)
			break ;
		if (!(node->next = init_buff()))
			return (-7);
		node = node->next;
	}
	if (i == 0)
		return (buff_flush(buff, line));
	else if (buff_flushn(buff, line, j) < 0)
		return (-6);
	return (1);
}
