#include "../miniRT.h"

int ft_color()
{
    int r;
    int g;
    int b;

    r = 255;
    g = 0;
    b = 152;
    return (r << 16 | g << 8 | b);
}

void    ft_display(t_win *w)
{
    int     x;
    char    *pix;
    int     y;
    char    *data;
    int     sl = 0;
    int     endn;
    int     bpp = 32;

    y = HEIGHT - 200;
    data = mlx_get_data_addr(w->img, &bpp, &sl, &endn);
    while (y > 0)
    {
        x = WIDTH - 200;
        while (x > 0)
        {
            pix = data + (x * (bpp / 8) + y * sl);
            *(int *)pix = ft_color();
            x--;
        }
        y--;
    }
    mlx_put_image_to_window(w->ptr, w->win, w->img, 0, 0);
}
