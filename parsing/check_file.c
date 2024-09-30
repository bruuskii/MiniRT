#include "../miniRT.h"

int ft_check_extention(char *s)
{
    char    *chck;

    if (!s)
        return (1);
    chck = ft_strchr(s, '.');
    if (!chck)
        return (printf("File with no extention !\n"), 1);
    else if (ft_strcmp(chck, ".rt"))
        return (printf("Wrong file extention !\n"), 1);
    return (0);
}

int ft_check_args(int ac)
{
    if (ac != 2)
    {
        printf("the program should be ran with :\n");
        printf("    [./miniRT] [filename]\n");
        return (1);
    }
    return (0);
}
