#include "BBQ_string.h"
#include "BBQ_file.h"

typedef struct s_args
{
	char	*file_as_string;
	int		desired_line_count;
	int		desired_line_length;
	int		line_count;
	int		line_length;
	char	empty;
	char	full;
	char	obstacle;
}	t_args;

int	argument_is_valid_c(t_args args)
{
	while (*args.file_as_string != '\0')
	{
		if (*args.file_as_string == args.empty
			|| *args.file_as_string == args.obstacle
			|| *args.file_as_string == args.full)
			args.line_length++;
		else if (*args.file_as_string == '\n')
		{
			args.line_count++;
			if (args.line_length != args.desired_line_length)
				return (0);
			if (args.line_count > args.desired_line_count)
				return (0);
			args.line_length = 0;
		}
		else
			return (0);
		args.file_as_string++;
	}
	return (1);
}

int	argument_is_valid_b(t_args args)
{
	args.desired_line_length = 0;
	while (args.file_as_string[args.desired_line_length] != '\n')
	{
		if (args.file_as_string[args.desired_line_length] == '\0')
			return (0);
		args.desired_line_length++;
	}
	args.line_length = 0;
	return (argument_is_valid_c(args));
}

int	argument_is_valid_a(t_args args)
{
	args.empty = *args.file_as_string;
	args.file_as_string++;
	if (*args.file_as_string < ' ' || *args.file_as_string > '~')
		return (0);
	args.obstacle = *args.file_as_string;
	args.file_as_string++;
	if (*args.file_as_string < ' ' || *args.file_as_string > '~')
		return (0);
	args.full = *args.file_as_string;
	while (*args.file_as_string != '\n')
	{
		if (*args.file_as_string == '\0')
			return (0);
		args.file_as_string++;
	}
	args.file_as_string++;
	return (argument_is_valid_b(args));
}

int	argument_is_valid(char *arg)
{
	t_args	args;

	args.file_as_string = read_file_to_string(arg);
	if (args.file_as_string[0] == '\0')
		return (0);
	if (args.file_as_string[0] < '0' || args.file_as_string[0] > '9')
		return (0);
	if (args.file_as_string[0] == '0')
		return (0);
	args.desired_line_count = string_to_int(args.file_as_string);
	if (args.desired_line_count <= 0)
		return (0);
	while (*args.file_as_string >= '0' && *args.file_as_string <= '9')
		args.file_as_string++;
	if (*args.file_as_string < ' ' || *args.file_as_string > '~')
		return (0);
	return (argument_is_valid_a(args));
}
