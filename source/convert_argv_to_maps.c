#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "map_argument_is_valid.h"
#include "BBQ_file.h"
#include "BBQ_string.h"
#include "valid_string_to_2d_char_map.h"
// Structure [map][x][y]

// padded with null char to allow iterating through x and y
//        [x] [x] [x] [x] [x]  [null]
// [y]    [.] [.] [.] [.] [\0]
// [y]    [.] [.] [.] [.] [\0]
// [y]    [.] [.] [.] [.] [\0]
// [y]    [.] [.] [.] [.] [\0]
// [y]    [\0][\0][\0][\0][\0]

void	write_map_error(int argument_index)
{
	char	index_c;

	index_c = argument_index + '0';
	write(1, "Map submitted as argument ", 27);
	write(1, &index_c, 1);
	write(1, " is an invalid!\n", 16);
}

#define MAX_MAP_COUNT 16

typedef struct s_args
{
	char	*map_string;
	char	***out_maps_buffer;
	char	***out_maps;
	int		valid_map_count;
	int		arg_index;
}	t_args;

char	***convert_argv_to_maps_a(t_args args, char **argv)
{
	args.out_maps = (char ***)malloc(sizeof(char **)
			* (args.valid_map_count + 1));
	args.arg_index = 0;
	while (args.arg_index < args.valid_map_count)
	{
		args.out_maps[args.arg_index] = args.out_maps_buffer[args.arg_index];
		args.arg_index++;
	}
	free(args.out_maps_buffer);
	args.out_maps[args.valid_map_count] = NULL;
	return (args.out_maps);
}

char	***convert_argv_to_maps(int argc, char **argv)
{
	t_args	args;

	args.out_maps_buffer = (char ***)malloc(sizeof(char **)
			* (MAX_MAP_COUNT + 1));
	args.arg_index = 1;
	args.valid_map_count = 0;
	while (args.arg_index < argc && args.arg_index < MAX_MAP_COUNT + 1)
	{
		if (!argument_is_valid(argv[args.arg_index]))
			write_map_error(args.arg_index);
		else
		{
			args.map_string = read_file_to_string(argv[args.arg_index]);
			args.out_maps_buffer[args.valid_map_count]
				= valid_string_to_2d_char_map(args.map_string);
			args.valid_map_count++;
			free(args.map_string);
		}
		args.arg_index++;
	}
	return (convert_argv_to_maps_a(args, argv));
}
