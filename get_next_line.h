/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:49:54 by pguthaus          #+#    #+#             */
/*   Updated: 2019/11/04 19:01:21 by pguthaus         ###   ########.fr       */
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
	size_t			eol;
	struct s_buff	*next;
}					t_buff;

int					get_next_line(int fd, char **line);

int					flush_to_eol(t_buff **buff, char **line);

int					read_do_buff(t_buff *buff, int fd, char **line);

#endif
