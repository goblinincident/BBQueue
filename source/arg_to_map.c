#include <stdlib.h>
#include "map_struct.h"
#include "BBQ_file.h"
#include "BBQ_string.h"

t_map_struct	arg_to_map(char ***char_maps, int map_index, char *arg)
{
	t_map_struct	map;
	char			*raw_file;
	int				i;

	raw_file = read_file_to_string(arg);
	map.char_array_map = char_maps[map_index];
	i = 0;
	map.map_size_y = string_to_int(raw_file);
	while (raw_file[i] >= '0' && raw_file[i] <= '9')
		i++;
	map.empty = raw_file[i];
	i++;
	map.object = raw_file[i];
	i++;
	map.full = raw_file[i];
	map.map_size_x = 0;
	while (char_maps[map_index][1][map.map_size_x])
		map.map_size_x++;
	free(raw_file);
	return (map);
}
