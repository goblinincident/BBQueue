#ifndef BBQ_FILE_H
# define BBQ_FILE_H

extern char	*read_file_to_string(const char *file_dir);
extern int	read_file(int file_descriptor, char **file_as_string_buffer);

#endif
