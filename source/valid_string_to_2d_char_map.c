#include <stdlib.h>
#include "BBQ_string.h"

typedef struct s_args
{	
	int		line_length;
	int		line_count;
	char	empty;
	char	obstacle;
	char	full;
	char	**out_map;
	int		x;
	int		y;
}	t_args;

char	**valid_string_to_2d_char_map_c(t_args args, char *str)
{
	args.x = 0;
	while (args.x < args.line_length + 1)
	{
		args.out_map[args.x][args.line_count] = '\0';
		args.x++;
	}
	args.out_map[args.line_length] = NULL;
	return (args.out_map);
}

char	**valid_string_to_2d_char_map_b(t_args args, char *str)
{
	args.x = 0;
	while (args.x < args.line_length + 1)
	{
		args.out_map[args.x] = (char *)malloc(sizeof(char)
				* (args.line_count + 1));
		args.x++;
	}
	args.x = 0;
	args.y = 0;
	while (*str != '\0')
	{
		if (*str == args.empty || *str == args.obstacle || *str == args.full)
		{
			args.out_map[args.x][args.y] = *str;
			args.x++;
		}
		else if (*str == '\n')
		{
			args.out_map[args.x][args.y] = '\0';
			args.x = 0;
			args.y++;
		}
		str++;
	}
	return (valid_string_to_2d_char_map_c(args, str));
}

char	**valid_string_to_2d_char_map(char *str)
{
	t_args	args;

	args.line_count = string_to_int(str);
	while (*str >= '0' && *str <= '9')
		str++;
	args.empty = *str;
	str++;
	args.obstacle = *str;
	str++;
	args.full = *str;
	while (*str != '\n')
		str++;
	str++;
	args.line_length = 0;
	while (str[args.line_length] != '\n')
		args.line_length++;
	args.out_map = (char **)malloc(sizeof(char *) * (args.line_length + 1));
	return (valid_string_to_2d_char_map_b(args, str));
}
