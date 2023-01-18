#include "./include/cub3d.h"

char	*ft_strndup(char *str, int n)
{
	char	*ptr;

	ptr = ft_calloc(n + 1, sizeof(char));
	ft_strlcpy(ptr, str, n);
	return (ptr);
}

void	free_matrix(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	exit_error(char *str)
{
	printf("Error\n");
	printf("%s\n", str);
	exit(1);
}

int	is_map_start(char *map_line)
{
	return (map_line[0] == '1' || map_line[0] == ' ');
}