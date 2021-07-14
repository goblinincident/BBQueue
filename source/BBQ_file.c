#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_FILE_SIZE 4096
#define NUMBER_OF_BYTES_TO_READ 512

int	read_file(int file_descriptor, char **file_as_string_buffer)
{
	int	total_bytes_read;
	int	size_of_bytes_read;

	total_bytes_read = 0;
	if (file_descriptor >= 0)
	{
		while (total_bytes_read <= MAX_FILE_SIZE)
		{
			size_of_bytes_read = read(
					file_descriptor,
					&(*file_as_string_buffer[total_bytes_read]),
					NUMBER_OF_BYTES_TO_READ
					% (MAX_FILE_SIZE - total_bytes_read));
			if (size_of_bytes_read <= 0)
			{
				size_of_bytes_read = 0;
				break ;
			}
			total_bytes_read += size_of_bytes_read;
			if (size_of_bytes_read < NUMBER_OF_BYTES_TO_READ)
				break ;
		}
	}
	(*file_as_string_buffer)[total_bytes_read] = '\0';
	return (total_bytes_read);
}

char	*read_file_to_string(const char *file_dir)
{
	int		file_descriptor;
	char	*file_as_string_buffer;
	char	*file_as_string;
	int		total_bytes_read;
	int		i;

	file_as_string_buffer = (char *)malloc((MAX_FILE_SIZE + 1) * sizeof(char));
	file_descriptor = open(file_dir, O_RDONLY);
	total_bytes_read = read_file(file_descriptor, &file_as_string_buffer);
	file_as_string = (char *)malloc((total_bytes_read + 1) * sizeof(char));
	i = 0;
	while (i < total_bytes_read)
	{
		file_as_string[i] = file_as_string_buffer[i];
		i++;
	}
	file_as_string[i] = '\0';
	free(file_as_string_buffer);
	return (file_as_string);
}
