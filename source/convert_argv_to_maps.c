#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
// Structure [map][x][y]

// padded with null char to allow iterating through x and y
//        [x] [x] [x] [x] [x]  [null]
// [y]    [.] [.] [.] [.] [\0]
// [y]    [.] [.] [.] [.] [\0]
// [y]    [.] [.] [.] [.] [\0]
// [y]    [.] [.] [.] [.] [\0]
// [y]    [\0][\0][\0][\0][\0]

// Temp size 10 * 12
// TEmp empty: '.' obstacle 'o'

#ifndef NULL
#define NULL ((void *)0)
#endif

// Translates file into a null-character terminated string
char *read_file_to_string(const char *file_dir)
{
    const int MAX_FILE_SIZE = 4096;
    const int NUMBER_OF_BYTES_TO_READ = 512;
    int file_descriptor;
    char *file_as_string_buffer;
    char *file_as_string;
    int size_of_bytes_read;
    int total_bytes_read;
    int i;

    // Reserve space
    file_as_string_buffer = (char *)malloc((MAX_FILE_SIZE + 1) * sizeof(char));
    total_bytes_read = 0;
    // Open file
    file_descriptor = open(file_dir, O_RDONLY);
    if (file_descriptor >= 0) // No file error
    {
        // Read until max file size
        while (total_bytes_read <= MAX_FILE_SIZE)
        {
            size_of_bytes_read = read(file_descriptor, &file_as_string_buffer[total_bytes_read], NUMBER_OF_BYTES_TO_READ % (MAX_FILE_SIZE - total_bytes_read));
            if (size_of_bytes_read <= 0) // Read error
            {
                size_of_bytes_read = 0;
                break;
            }
            total_bytes_read += size_of_bytes_read;
            // Stop when max file size, or end of file, reached
            if (size_of_bytes_read < NUMBER_OF_BYTES_TO_READ)
                break;
        }
    }
    else // File open error
        file_as_string_buffer[0] = '\0';

    // Trim buffer
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

// Reads first characters as int (must be positive)
int string_to_int(char *str)
{
    int number;

    number = 0;
    while (*str >= '0' && *str <= '9')
    {
        number *= 10;
        number += *str - '0';
        str++;
    }

    return (number);
}

// Checks the submitted arguments match BBQ criteria
int argument_is_valid(char *arg)
{
    char *file_as_string;
    int desired_line_length;
    int line_length;
    int desired_line_count;
    int line_count;
    char empty;
    char obstacle;
    char full;

    file_as_string = read_file_to_string(arg);
    // Check file read correctly
    if (file_as_string[0] == '\0')
        return (0);
    // Check the first value is valid number (number of lines)
    if (file_as_string[0] < '0' || file_as_string[0] > '9')
        return (0);
    if (file_as_string[0] == '0')
        return (0);
    // Check desired line count is greater than zero
    desired_line_count = string_to_int(file_as_string);
    if (desired_line_count <= 0)
        return (0);
    // Check next value is printable
    while (*file_as_string >= '0' && *file_as_string <= '9')
        file_as_string++;
    if (*file_as_string < ' ' || *file_as_string > '~')
        return (0);

    empty = *file_as_string;

    // Check next value is printable
    file_as_string++;
    if (*file_as_string < ' ' || *file_as_string > '~')
        return (0);

    obstacle = *file_as_string;

    // Check next value is printable
    file_as_string++;
    if (*file_as_string < ' ' || *file_as_string > '~')
        return (0);

    full = *file_as_string;

    // Move to next line
    while (*file_as_string != '\n')
    {
        // Check premature EOF
        if (*file_as_string == '\0')
            return (0);
        file_as_string++;
    }
    file_as_string++;

    // Get desired line length
    desired_line_length = 0;
    while (file_as_string[desired_line_length] != '\n')
    {
        // Check premature EOF
        if (file_as_string[desired_line_length] == '\0')
            return (0);
        desired_line_length++;
    }

    line_count = 0;
    line_length = 0;
    while (*file_as_string != '\0')
    {
        if (*file_as_string == empty || *file_as_string == obstacle || *file_as_string == full)
            line_length++;
        else if (*file_as_string == '\n')
        {
            line_count++;
            // Check line length
            if (line_length != desired_line_length)
                return (0);
            // Check line count
            if (line_count > desired_line_count)
                return (0);
            line_length = 0;
        }
        else // Check unexpected character
            return (0);
        file_as_string++;
    }

    // If it passed all that. It's probably good :)
    return (1);
}

// Converts a valid string into a null terminated 2d char array
char **valid_string_to_2d_char_map(char *str)
{
    int line_length;
    int line_count;
    char empty;
    char obstacle;
    char full;
    char **out_map;
    int x;
    int y;

    line_count = string_to_int(str);
    // Next value
    while (*str >= '0' && *str <= '9')
        str++;
    empty = *str;
    // Next value
    str++;
    obstacle = *str;
    // Next value
    str++;
    full = *str;
    // Next line
    while (*str != '\n')
        str++;
    str++;
    // Line length
    line_length = 0;
    while (str[line_length] != '\n')
        line_length++;

    // Reserve map memory
    out_map = (char **)malloc(sizeof(char *) * (line_length + 1));
    x = 0;
    while (x < line_length + 1)
    {
        out_map[x] = (char *)malloc(sizeof(char) * (line_count + 1));
        x++;
    }

    // Populate map:
    // padded with null char to allow iterating through x and y
    //        [x] [x] [x] [x] [x]  [null]
    // [y]    [.] [.] [.] [.] [\0]
    // [y]    [.] [.] [.] [.] [\0]
    // [y]    [.] [.] [.] [.] [\0]
    // [y]    [.] [.] [.] [.] [\0]
    // [y]    [\0][\0][\0][\0][\0]
    x = 0;
    y = 0;
    while (*str != '\0')
    {
        if (*str == empty || *str == obstacle || *str == full)
        {
            out_map[x][y] = *str;
            x++;
        }
        else if (*str == '\n')
        {
            out_map[x][y] = '\0';
            x = 0;
            y++;
        }
        str++;
    }
    x = 0;
    while (x < line_length + 1)
    {
        out_map[x][line_count] = '\0';
        x++;
    }
    out_map[line_length] = NULL;

    return (out_map);
}

// Error message
void write_map_error(int argument_index)
{
    char index_c;

    index_c = argument_index + '0';
    write(1, "Map submitted as argument ", 27);
    write(1, &index_c, 1);
    write(1, " is an invalid!\n", 16);
}

// Creates a null terminated array of maps
char ***convert_argv_to_maps(int argc, char **argv)
{
    const int MAX_MAP_COUNT = 16;
    char *map_string;
    char ***out_maps_buffer;
    char ***out_maps;
    int valid_map_count;
    int arg_index;

    // Create buffer to temporarily hold maps
    out_maps_buffer = (char ***)malloc(sizeof(char **) * (MAX_MAP_COUNT + 1));

    arg_index = 1;
    valid_map_count = 0;
    while (arg_index < argc && arg_index < MAX_MAP_COUNT + 1)
    {
        // Check argument file is present and formatted correclty
        if (!argument_is_valid(argv[arg_index]))
            write_map_error(arg_index);
        else
        {
            // Generate and add map to buffer
            map_string = read_file_to_string(argv[arg_index]);
            out_maps_buffer[valid_map_count] = valid_string_to_2d_char_map(map_string);
            valid_map_count++;
            free(map_string);
        }
        arg_index++;
    }

    // Create map holder of correct size
    out_maps = (char ***)malloc(sizeof(char **) * (valid_map_count + 1));
    arg_index = 0;
    while (arg_index < valid_map_count)
    {
        // Copy contents from buffer
        out_maps[arg_index] = out_maps_buffer[arg_index];
        arg_index++;
    }
    free(out_maps_buffer);
    
    // null terminate
    out_maps[valid_map_count] = NULL;

    return (out_maps);
}
