#include "../includes/minirt_bonus.h"

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

void put_pixel_to_image(char *img_data, int x, int y, int color)
{
    int offset;

    offset = (y * WINDOW_WIDTH + x) * 4;
    *(unsigned int*)(img_data + offset) = color;
}

void render_scene(void *mlx, void *win, t_scene *scene)
{
    int x, y;
    t_ray *ray;
    t_hit *hit;
    t_vctr *color;
    t_color *clr;

    clr = malloc(sizeof(t_color));
    clr->r = 200;
    clr->g = 100;
    clr->b = 50;
    void *img;
    char *img_data;
    int bits_per_pixel, size_line, endian;

    img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    y = 0;
    while (y < WINDOW_HEIGHT)
    {
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            double u = (double)x / (WINDOW_WIDTH - 1);
            double v = (double)y / (WINDOW_HEIGHT - 1);
            ray = create_ray(scene->cam, u, v);
            hit = intersect_sphere(ray, (t_sp *)scene->obj);
            if (hit->hit)
            {
                color = calculate_lighting(ray, hit->point, hit->normal, scene, scene->obj->mtrl, clr);
                put_pixel_to_image(img_data, x, y, create_trgb(0, (int)(color->x * 255), (int)(color->y * 255), (int)(color->z * 255)));
            }
            else
                put_pixel_to_image(img_data, x, y, create_trgb(0, 50, 50, 50));
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(mlx, win, img, 0, 0);
    mlx_destroy_image(mlx, img);
}

int main(int ac, char **av)
{
    (void)ac;
    t_scene *scene;
    t_data data;

    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);
    data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT Bonus");
    if (!data.win)
    {
        free(data.mlx);
        return (1);
    }
    scene = data_input(av[1]);
    if (!scene)
        return (1);
    render_scene(data.mlx, data.win, scene);
    mlx_key_hook(data.win, (int (*)(int, void *))ft_escape_key, &data);
    mlx_hook(data.win, 17, 0, ft_close, &data);
    mlx_loop(data.mlx);
    return (0);
}
