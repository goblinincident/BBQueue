#include "fragments/print_map.c"
#include "fragments/convert_argv_to_maps.c"

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
        print_map(maps[map_i]);
        map_i++;
    }
}