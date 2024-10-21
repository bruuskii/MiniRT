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
    t_vec3 *color;
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
            ray = create_ray(scene->camera, u, v);
            hit = intersect_sphere(ray, scene->sphere);
            if (hit->hit)
            {
                color = calculate_lighting(ray, hit->point, hit->normal, scene, scene->sphere->material);
                put_pixel_to_image(img_data, x, y, create_trgb(0, (int)(color->x * 255), (int)(color->y * 255), (int)(color->z * 255)));
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


int ft_escape_key(int keycode, t_data *data)
{
    if (keycode == 65307)
    {
        mlx_destroy_window(data->mlx, data->win);
        // mlx_destroy_display(data->mlx);
        free(data->mlx);
        exit(0);
    }
    return (0);
}

int ft_close(void *param)
{
    (void)param;
    exit(0);
    return (0);
}
int main(int argc, char **argv)
{
    t_scene *scene;
    printf("bdit1\n");


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

    // Allocate memory for the scene and its components
    

    // scene->camera = malloc(sizeof(t_camera));
    // if (!scene->camera)
    // {
    //     free(scene);
    //     return (1);
    // }
    
    // scene->sphere = malloc(sizeof(t_sphere));
    // if (!scene->sphere)
    // {
    //     free(scene->camera);
    //     free(scene);
    //     return (1);
    // }

    // scene->sphere->material = malloc(sizeof(t_material));
    // if (!scene->sphere->material)
    // {
    //     free(scene->sphere);
    //     free(scene->camera);
    //     free(scene);
    //     return (1);
    // }

    // scene->light = malloc(sizeof(t_light));
    // if (!scene->light)
    // {
    //     free(scene->sphere->material);
    //     free(scene->sphere);
    //     free(scene->camera);
    //     free(scene);
    //     return (1);
    // }

    // scene->ambient_light = malloc(sizeof(t_vec3));
    // if (!scene->ambient_light)
    // {
    //     free(scene->light);
    //     free(scene->sphere->material);
    //     free(scene->sphere);
    //     free(scene->camera);
    //     free(scene);
    //     return (1);
    // }

    scene = data_input(argv[1]);

    if (!scene)
        return (1);

    // Initialize scene components
    // scene->camera->position = vec3_create(0, 2, 0);
    // scene->camera->direction = vec3_create(0, 0, 1);
    // scene->camera->fov = 35;
    // scene->sphere->center = vec3_create(0, 2, 5);
    // scene->sphere->radius = 1;
    // scene->sphere->material->color = vec3_create(1, 0, 0);  // Red
    // scene->sphere->material->ambient = 0.1;
    // scene->sphere->material->diffuse = 0.5;
    // scene->sphere->material->specular = 0.5;
    // scene->sphere->material->shininess = 10;

    // scene->light->position = vec3_create(5, 5, -5);
    // scene->light->color = vec3_create(1, 1, 1);  // White light
    // scene->light->intensity = 1;

    // scene->ambient_light->x = 0.1;
    // scene->ambient_light->y = 0.1;
    // scene->ambient_light->z = 0.1;

    if (ft_check_args(argc))
        return (1);
    if (ft_check_extention(argv[1]))
        return (1);
    printf("bdit\n");
    render_scene(data.mlx, data.win, scene);

    printf("dezt");
    mlx_key_hook(data.win, (int (*)(int, void *))ft_escape_key, &data);
    mlx_hook(data.win, 17, 0, ft_close, &data);
    mlx_loop(data.mlx);

    // Free allocated memory (add cleanup code here)
    // free(scene->ambient_light);
    // free(scene->light);
    // free(scene->sphere->material);
    // free(scene->sphere);
    // free(scene->camera);
    // free(scene);
    // free(data.mlx);
    return (0);
}
