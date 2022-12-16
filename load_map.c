#include "./include/cub3d.h"

char **load_map(char *map_name)
{
	static char buffer[2];
	char *map;
	char *ref;
	int n_read;
	int fd;

	fd = open(map_name, O_RDONLY);
	if (fd <= 0)
		return (NULL);
	map = ft_strdup("");
	n_read = 1;
	while (n_read)
	{
		n_read = read(fd, buffer, 1);
		if (n_read == -1)
			return (NULL);
		ref = map;
		map = ft_strjoin(map, buffer);
		free(ref);
	}
	close(fd);
	return (ft_split(map, '\n'));
}
