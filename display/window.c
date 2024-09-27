#include "../miniRT.h"

t_win   *ft_window(int height, int width)
{
    t_win   *win;

    win = malloc(sizeof(t_win));
    if (!win)
        return (NULL);
    win->height = height;
    win->width = width;
    win->ptr = mlx_init();
    win->win = mlx_new_window(win->ptr, win->height, win->width, "miniRT");
    win->img = mlx_new_image(win->ptr, win->height, win->width);
    return (win);
}

void    ft_free_win(t_win *w)
{
	if (w->img)
		mlx_destroy_image(w->ptr, w->img);
	if (w->win)
		mlx_destroy_window(w->ptr, w->win);
	if (w->ptr)
	{
		mlx_destroy_display(w->ptr);
		free(w->ptr);
	}
	free(w);
	exit(0);
}
