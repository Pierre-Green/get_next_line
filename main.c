/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:56:37 by pguthaus          #+#    #+#             */
/*   Updated: 2019/11/18 17:14:44 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include "get_next_line.h"
#include <stdio.h>

int				main(int ac, char **av)
{
	int			fd;
	int			ret;
	char		*buff;
	size_t		line;

	(void)ac;
	buff = NULL;
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (-1);
	line = 0;
	while ((ret = get_next_line(fd, &buff)) >= 0)
	{
		line++;
		printf("%4zu#%d %s\n", line, ret, buff);
		free((void *)buff);
		if (ret == 0)
			break ;
	}
	return (ret);
}
