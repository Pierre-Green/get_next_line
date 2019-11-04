/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:49:24 by pguthaus          #+#    #+#             */
/*   Updated: 2019/11/04 19:08:34 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_buff		*get_initial_buff()
{
	t_buff			*buff;

	if (!(buff = malloc(sizeof(t_buff))))
		return (NULL);
	buff->eol = 0;
	buff->len = 0;
	buff->next = NULL;
	return (buff);
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
			if (ptr->eol || ptr->buff[0] == '\n')
				return (flush_to_eol(&buff, line));
			ptr = ptr->next;
		}
	else if (!(buff = get_initial_buff()))
		return (-1);
	if (read(fd, tmp, 0) < 0)
		return (-1);
	if ((read_ret = read_do_buff(buff, fd, line)) >= 0)
	{
		if (read_ret % BUFF_SIZE == 0)
			return (flush_to_eol(&buff, line));
		else
		{
			flush_to_eol(&buff, line);
			return (0);
		}
	}
	return (-1);
}
