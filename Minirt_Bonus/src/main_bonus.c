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

void render_scene(void *img, t_scene *scene)
{
    int x, y;
    t_ray ray;
    t_sp *sp;
    t_hit *hit;
    t_vctr color;
    char *img_data;
    int bits_per_pixel, size_line, endian;

    img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    sp = (t_sp *)scene->sp;
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
            x++;
        }
        y++;
    }
}

void render_scene_plane(void *img, t_scene *scene)
{
    int x, y;
    t_ray ray;
    t_plane *sp;
    t_hit *hit;
    t_vctr color;
    char *img_data;
    int bits_per_pixel, size_line, endian;

    img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    sp = (t_plane *)scene->pl;
    y = 0;
    while (y < WINDOW_HEIGHT)
    {
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            double u = (double)x / (WINDOW_WIDTH - 1);
            double v = (double)y / (WINDOW_HEIGHT - 1);
            ray = create_ray(scene->cam, u, v);
            hit = intersect_plane(&ray, scene->pl);
            if (hit->hit)
            {
                color = calculate_lighting(&ray, hit->point, hit->normal, scene, sp->mtrl);
                put_pixel_to_image(img_data, x, y, create_trgb(0, (int)(color.x), (int)(color.y), (int)(color.z)));
            }
            x++;
        }
        y++;
    }
}

void render_scene_cy(void *img, t_scene *scene)
{
    int x, y;
    t_ray ray;
    t_cylinder *cy;
    t_hit *hit;
    t_vctr color;
    char *img_data;
    int bits_per_pixel, size_line, endian;

    img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    cy = (t_cylinder *)scene->cy;
    y = 0;
    while (y < WINDOW_HEIGHT)
    {
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            double u = (double)x / (WINDOW_WIDTH - 1);
            double v = (double)y / (WINDOW_HEIGHT - 1);
            ray = create_ray(scene->cam, u, v);
            hit = intersect_cylinder(&ray, scene->cy);
            if (hit->hit)
            {
                color = calculate_lighting(&ray, hit->point, hit->normal, scene, cy->mtrl);
                put_pixel_to_image(img_data, x, y, create_trgb(0, (int)(color.x), (int)(color.y), (int)(color.z)));
            }
            x++;
        }
        y++;
    }
}

void    ft_render_sphere(t_sp **sphere, void *img, t_scene *scene)
{
    *sphere = (t_sp *)(scene->sp);
    (*sphere)->mtrl = malloc(sizeof(t_material));
    (*sphere)->mtrl->color = *(*sphere)->color;
    (*sphere)->mtrl->ambient = scene->alight->ratio;
    (*sphere)->mtrl->diffuse = 0.5;
    (*sphere)->mtrl->specular = 0.5;
    (*sphere)->mtrl->shininess = 60;
    render_scene(img, scene);
}

int main(int ac, char **av)
{
    t_data   data;
    t_scene *scene;
    t_sp    *sphere;
    t_plane *plane;
    void    *img;

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
    img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (scene->pl)
    {
        while (scene->pl)
        {
            plane = (t_plane *)(scene->pl);
            plane->mtrl = malloc(sizeof(t_material));
            plane->mtrl->color = *plane->color;
            plane->mtrl->ambient = scene->alight->ratio;
            plane->mtrl->diffuse = 0.5;
            plane->mtrl->specular = 0.5;
            plane->mtrl->shininess = 60;
            render_scene_plane( img, scene);
            scene->pl = scene->pl->next;
        }
    }
    if (scene->sp)
    {
        while (scene->sp)
        {

            sphere = (t_sp *)(scene->sp);
            ft_render_sphere(&sphere, img, scene);
            scene->sp = scene->sp->next;
        }
    }
    if (scene->cy)
    {
        while (scene->cy)
        {
            t_cylinder  *cy;
            cy = (t_cylinder *)(scene->cy);
            cy->mtrl = malloc(sizeof(t_cylinder));
            cy->mtrl->color = *cy->color;
            cy->mtrl->ambient = scene->alight->ratio;
            cy->mtrl->diffuse = 0.5;
            cy->mtrl->specular = 0.5;
            cy->mtrl->shininess = 60;
            render_scene_cy(img, scene);
            scene->cy = scene->cy->next;
        }
    }
    mlx_put_image_to_window(data.mlx, data.win, img, 0, 0);
    mlx_key_hook(data.win, (int (*)(int, void *))ft_escape_key, &data);
    mlx_hook(data.win, 17, 0, ft_close, &data);
    mlx_loop(data.mlx);
    return (0);
}
