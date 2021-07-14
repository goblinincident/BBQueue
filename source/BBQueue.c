#include "convert_argv_to_maps.h"
#include "print_map.h"
#include "map_struct.h"

// TODO:
// ◦Should there be no passed arguments, your program must
// be able to read onthe standard input.

int	main(int argc, char **argv)
{
	char	***maps;
	int		map_i;

	if (argc == 1)
	{
	}
	maps = convert_argv_to_maps(argc, argv);
	map_i = 0;
	while (maps[map_i])
	{
		print_array_map(maps[map_i]);
		map_i++;
	}
}
