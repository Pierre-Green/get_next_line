/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:49:54 by pguthaus          #+#    #+#             */
/*   Updated: 2019/11/12 15:44:53 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
# 	define BUFFER_SIZE 64
# endif

typedef struct		s_buff
{
	char			buff[BUFFER_SIZE];
	size_t			len;
	char			eol;
	char			eof;
	struct s_buff	*next;
}					t_buff;

int					get_next_line(int fd, char **line);

int					flush_to_eol(t_buff **buff, char **line);

t_buff				*clear_buff_next(t_buff *buff);

void				trim_buff(t_buff *buff, unsigned int nl);

#endif
