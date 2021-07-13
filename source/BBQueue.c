#include "convert_argv_to_maps.h"
#include "print_map.h"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        // TODO:
        // ◦Should there be no passed arguments, your program must be able to read onthe standard input.
    }
    char ***maps = convert_argv_to_maps(argc, argv);

    int map_i = 0;
    while (maps[map_i])
    {
        print_array_map(maps[map_i]);
        map_i++;
    }
}