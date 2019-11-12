#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "stdio.h"

int				main(int ac, char **av)
{
	int			fd, ret, count;
	char		*line;

	(void)ac;
	fd = open(av[1], O_RDONLY);
	count = 0;
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		count++;
		printf("%3d#%d %s\n", count, ret, line);
		free(line);
		if (ret == 0)
			break ;
	}
	return (0);
}
