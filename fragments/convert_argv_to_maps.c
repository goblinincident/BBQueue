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
char ***convert_argv_to_maps(int argc, char** argv)
{
    argc = 2;
    const int X = 10;
    const int Y = 12;
    int x = 0;
    int y = 0;

    // reserve memory
    char ***out_maps = (char***)malloc(sizeof(char **) * (argc - 1));

    char **map = (char **)malloc(sizeof(char *) * (X + 1));
    while (x < X + 1)
    {
        map[x] = (char *)malloc(sizeof(char) * Y);
        x++;
    }

    // empty map
    x = 0;
    while (x < X)
    {
        y = 0;
        while (y < Y)
        {
            map[x][y] = '.';
            y++;   
        }
        map[x][y] = '\0';
        x++;
    }
    y = 0;
    while (y < Y)
    {
        map[x][y] = '\0';
        y++;
    }
    map[x + 1] = (void *)0;
    
    // temp obstacle
    map[2][4] = 'o';
    map[4][1] = 'o';
    map[8][7] = 'o';

    // output: array of 1 map, x 10, y 12, 3 obstacles
    out_maps[0] = map;
}