#include "../../inc/cube3d.h"

int	count_occurrences(char **lines, const char *target)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (lines[i] != NULL)
    {
        if (ft_strncmp(lines[i], target, strlen(target)) == 0 &&
            (lines[i][strlen(target)] == ' ' || lines[i][strlen(target)] == '\t'))
        {
            count++;
        }
        i++;
    }
    return (count);
}

int	validate_textures(char **lines)
{
    const char	*required_textures[] = {"NO", "SO", "WE", "EA","F","C"};
    int			num_textures;
    int			i;
    int			count;


    num_textures = 6;
    i = 0;
    while (i < num_textures)
    {
        // printf(" the string to look for %s\n",required_textures[i]);
        count = count_occurrences(lines, required_textures[i]);
        if (count != 1)
        {
                    // printf(" the string to look for %s\n",required_textures[i]);
            write(2,"error :",8);
            return (0);
        }
        // printf("string found : %s",required_textures[i]);
        i++;
    }
    return (1);
}