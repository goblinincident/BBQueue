#include <stdlib.h>
#include <unistd.h>

#include "convert_argv_to_maps.h"
#include "print_map.h"
#include "map_struct.h"
#include "map_struct.h"
#include "BBQ_string.h"
#include "BBQ_file.h"
#include "map_argument_is_valid.h"
#include "arg_to_map.h"

// TODO:
// ◦Should there be no passed arguments, your program must
// be able to read onthe standard input.

#define MAX_MAPS 128

int	main(int argc, char **argv)
{
	t_map_struct	*maps;
	int				valid_map_count;
	int				i;
	char			***char_maps;
	int				valid_map_found;

	maps = (t_map_struct *)malloc(sizeof(t_map_struct) * (MAX_MAPS + 1));
	char_maps = convert_argv_to_maps(argc, argv);
	valid_map_count = 0;
	i = -1;
	while (i++ < argc)
	{
		if (argc == 1)
		{
		}
		if (!argument_is_valid(argv[i]))
			write(1, "Map Error!\n", 11);
		else
		{
			maps[valid_map_count]
				= arg_to_map(char_maps, valid_map_count, argv[i]);
			valid_map_count++;
		}
	}
	print_array_map(maps[0].char_array_map);
}
