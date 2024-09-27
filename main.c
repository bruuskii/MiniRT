#include "miniRT.h"

int main()
{
    t_win *win;

    win = ft_window(800, 800);
    if (!win)
        return (1);
    ft_display(win);
    mlx_key_hook(win->win, ft_escape_key, win);
    mlx_hook(win->win, 17, 0, ft_close, win);
    mlx_loop(win->ptr);
}
