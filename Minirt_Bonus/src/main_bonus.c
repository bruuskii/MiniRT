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
    t_ray ray;
    t_sp *sp;
    t_hit *hit;
    t_vctr color;
    void *img;
    char *img_data;
    int bits_per_pixel, size_line, endian;

    img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    sp = (t_sp *)scene->obj;
    if (sp)
        printf("kayna %f\n", sp->color->x);
    y = 0;
    while (y < WINDOW_HEIGHT)
    {
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            double u = (double)x / (WINDOW_WIDTH - 1);
            double v = (double)y / (WINDOW_HEIGHT - 1);
            ray = create_ray(scene->cam, u, v);
            hit = intersect_sphere(&ray, sp);
            if (hit->hit)
            {
                color = calculate_lighting(&ray, hit->point, hit->normal, scene, sp->mtrl);
                put_pixel_to_image(img_data, x, y, create_trgb(0, (int)(color.x ), (int)(color.y), (int)(color.z)));
            }
            else
                put_pixel_to_image(img_data, x, y, create_trgb(0, 50, 50, 50));  // Background color
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(mlx, win, img, 0, 0);
    mlx_destroy_image(mlx, img);
}


// int ft_escape_key(int keycode, t_data *data)
// {
//     if (keycode == 65307)
//     {
//         mlx_destroy_window(data->mlx, data->win);
//         mlx_destroy_display(data->mlx);
//         free(data->mlx);
//         exit(0);
//     }
//     return (0);
// }

// int ft_close(void *param)
// {
//     (void)param;
//     exit(0);
//     return (0);
// }
int main(int ac, char **av)
{
    t_data data;
    t_scene *scene;
    t_sp    *sphere;
    
    if (ac != 2)
        return (1);
    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);
    data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT Bonus");
    if (!data.win)
    {
        mlx_destroy_display(data.mlx);
        free(data.mlx);
        return (1);
    }
    scene =  data_input(av[1]);
    while (scene->obj)
    {
        if (scene->obj->type == SPHERE)
        {
            sphere = (t_sp *)(scene->obj);
            sphere->mtrl = malloc(sizeof(t_material));
            sphere->mtrl->color = *sphere->color;
            sphere->mtrl->ambient = scene->alight->ratio;
            sphere->mtrl->diffuse = 0.5;
            sphere->mtrl->specular = 0.5;
            sphere->mtrl->shininess = 60;
            render_scene(data.mlx, data.win, scene);
        }

    }
    mlx_key_hook(data.win, (int (*)(int, void *))ft_escape_key, &data);
    mlx_hook(data.win, 17, 0, ft_close, &data);
    mlx_loop(data.mlx);
    return (0);
}