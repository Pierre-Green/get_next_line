/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 16:09:13 by pguthaus          #+#    #+#             */
/*   Updated: 2019/10/18 18:34:38 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buff		*init_buff()
{
	t_buff	*buff;

	if (!(buff = malloc(sizeof(t_buff))))
		return (NULL);
	buff->len= 0;
	buff->next = 0;
	return (buff);
}

int				buff_clear(t_buff *buff)
{
	t_buff		*tmp;

	while (buff)
	{
		tmp = buff;
		buff = buff->next;
		free(tmp);
	}
	return (1);
}

int				buff_flush(t_buff *buff, char **line)
{
	size_t		len;
	t_buff		*node;
	size_t		i;
	size_t		pos;

	node = buff;
	while (node)
	{
		len += node->len;
		node = node->next;
	}
	if (!(*line = malloc((len + 1) * sizeof(char))))
		return (-1);
	node = buff;
	pos = 0;
	while (node)
	{
		i = 0;
		while (i < node->len)
		{
			(*line)[pos + i] = node->buff[i];
			i++;
		}
		pos += i;
		node = node->next;
	}
	(*line)[len] = 0;
	buff_clear(buff);
	return (1);
}

int				buff_flushn(t_buff *buff, char **line, size_t len)
{
	t_buff		*node;
	t_buff		*tmp;
	size_t		t_len;
	size_t		i;
	size_t		j;

	node = buff;
	t_len = 0;
	while (node && node->next)
	{
		t_len += node->len;
		node = node->next;
	}
	t_len += len;
	if (!(*line = malloc(t_len * sizeof(char))))
		return (-1);
	(*line)[t_len] = 0;
	node = buff;
	j = 0;
	while (node && node->next)
	{
		i = 0;
		while (i < node->len)
		{
			(*line)[i + j] = node->buff[i];
			i++;
		}
		tmp = node;
		node = node->next;
		free(tmp);
		j += i;
	}
	i = 0;
	while (i < len)
	{
		(*line)[i + j] = node->buff[i];
		i++;
	}
	return (1);
}
int				buff_write(t_buff *buff, char *src, size_t len)
{
	size_t		ret;

	ret = len;
	while (buff->len < len)
	{
		if (src[buff->len] == '\n')
			ret = buff->len;
		buff->buff[buff->len] = src[buff->len];
		buff->len++;
	}
	return (ret);
}
