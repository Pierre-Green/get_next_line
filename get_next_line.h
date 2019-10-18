/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:49:54 by pguthaus          #+#    #+#             */
/*   Updated: 2019/10/18 17:01:55 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_buff
{
	char			buff[BUFF_SIZE];
	size_t			len;
	struct s_buff	*next;
}					t_buff;

int					get_next_line(int fd, char **line);

t_buff				*init_buff();

int					buff_clear(t_buff *buff);

int					buff_write(t_buff *buff, char *src, size_t len);

int					buff_flush(t_buff *buff, char **line);

int					buff_flushn(t_buff *buff, char **line, size_t len);

#endif
