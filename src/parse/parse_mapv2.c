#include "../../inc/cube3d.h"

int count_till_newline(char *s)
{
    int i = 0;
    while(s[i] && s[i] != '\n')
        i++;
    return (i);
}

int get_bigger_mapline(char **s)
{
    int i = 0;
    int bigger_value;
    
    if (!s || !s[0])
        return 0;
        
    bigger_value = count_till_newline(s[0]);
    
    while(s[i])
    {
        int current_length = count_till_newline(s[i]);
        if (current_length > bigger_value)
            bigger_value = current_length;
        i++;
    }
    return bigger_value;
}

int get_line_of_biggervalue(char **s)
{
    int i = 0;
    int max_length;
    
    if (!s || !s[0])
        return 0;
        
    max_length = get_bigger_mapline(s);
    
    while(s[i])
    {
        if(count_till_newline(s[i]) == max_length)
            return i;
        i++;
    }
    return i - 1;
}