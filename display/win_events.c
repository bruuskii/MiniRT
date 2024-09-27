#include "../miniRT.h"

int ft_escape_key(int key, void *param)
{
    if (key ==  65307)
    {
        ft_free_win((t_win *)param);
        param = NULL;
    }
    return (0);
}

int ft_close(t_win *param)
{
    ft_free_win((t_win *)param);
    param = NULL;
    return (0);
}
