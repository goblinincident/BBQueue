#ifndef MAP_STRUCT_H
# define MAP_STRUCT_H

typedef struct square
{
	int		top_left_corner_x;
	int		top_left_corner_y;
	int		size;
}	t_square;

typedef struct map_struct
{
	int		map_size_x;
	int		map_size_y;
	char	empty;
	char	full;
	char	object;
	char	**char_array_map;
}	t_map_struct;

#endif