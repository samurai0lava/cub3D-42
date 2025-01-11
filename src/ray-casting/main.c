#include "../../inc/cube3d.h"

int main()
{
    t_cube *cube;

    cube = (t_cube *)malloc(sizeof(t_cube));
    init_mlx(cube);    

    return (0);
}