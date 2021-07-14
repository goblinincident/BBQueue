#include <stdio.h>

void	print_array_map(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[x][y])
	{
		while (map[x])
		{
			printf("%c", map[x][y]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}
