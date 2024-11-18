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


    double  ft_magnitude(t_vctr *vec)
    {
        return (sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z)));
    }

    t_vctr amb_color(t_vctr ambiant, t_material *mtrl)
    {
        t_vctr amb;
        t_vctr color = mtrl->color;   
        double ambient = mtrl->ambient; 

        amb.x = ambiant.x * color.x * ambient / 255;
        amb.y = ambiant.y * color.y * ambient / 255;
        amb.z = ambiant.z * color.z * ambient / 255;

        return amb;
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
                double u = ((double)x / (WINDOW_WIDTH - 1));
                double v = ((double)y / (WINDOW_HEIGHT - 1));
                ray = create_ray(scene->cam, u, v);
                hit = intersect_sphere(&ray, scene->sp);
                if (hit->hit)
                {
                    color = calculate_lighting(&ray, hit, scene, *sp->mtrl);
                    put_pixel_to_image(img_data, x, y, create_trgb(0, (int)(color.x), (int)(color.y), (int)(color.z)));

                }
                free(hit);
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
                double u = ((double)x / (WINDOW_WIDTH - 1)); 
                double v = ((double)y / (WINDOW_HEIGHT - 1)); 
                ray = create_ray(scene->cam, u, v);
                hit = intersect_plane(&ray, scene->pl);
                if (hit->hit)
                {
                    color = calculate_lighting(&ray, hit, scene, *sp->mtrl);
                    put_pixel_to_image(img_data, x, y, create_trgb(0, (int)(color.x), (int)(color.y), (int)(color.z)));

                }
                free(hit);
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
                double u = ((double)x / (WINDOW_WIDTH - 1));
                double v = ((double)y / (WINDOW_HEIGHT - 1));
                ray = create_ray(scene->cam, u, v);
                hit = intersect_cylinder(&ray, cy);
                if (hit->hit)
                {
                    color = calculate_lighting(&ray, hit, scene, *cy->mtrl);
                    put_pixel_to_image(img_data, x, y, create_trgb(0, (int)(color.x), (int)(color.y), (int)(color.z)));
                }
                free(hit);
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
        t_win   *data;
        t_scene *scene;
        t_sp    *sphere;
        t_plane *plane;

        if (ac != 2)
            return (1);
        data = malloc(sizeof(t_win));
        if (!data)
            return (1);
        data->ptr = mlx_init();
        if (!data->ptr)
            return (1);
        data->win = mlx_new_window(data->ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT Bonus");
        if (!data->win)
        {
            mlx_destroy_display(data->ptr);
            free(data->ptr);
            return (1);
        }
        scene =  data_input(av[1]);
        data->img = mlx_new_image(data->ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
        if (scene->pl)
        {
            printf("light x ==  %f\n", scene->light->dir->x);
            while (scene->pl)
            {
                plane = (t_plane *)(scene->pl);
                plane->mtrl = malloc(sizeof(t_material));
                plane->mtrl->color = *plane->color;
                plane->mtrl->ambient = scene->alight->ratio;
                plane->mtrl->diffuse = 0.5;
                plane->mtrl->specular = 0.5;
                plane->mtrl->shininess = 60;
                render_scene_plane( data->img, scene);
                free(scene->pl->mtrl);
                free(scene->pl->point);
                free(scene->pl->normal);
                free(scene->pl->color);
                scene->pl = scene->pl->next;
            }
        }
        if (scene->sp)
        {
            while (scene->sp)
            {

                sphere = (t_sp *)(scene->sp);
                ft_render_sphere(&sphere, data->img, scene);
                free(scene->sp->cntr);
                free(scene->sp->color);
                free(scene->sp->mtrl);
                scene->sp = scene->sp->next;
            }
        }
        if (scene->cy)
        {
            while (scene->cy)
            {
                t_cylinder  *cy;
                cy = (t_cylinder *)(scene->cy);
                cy->mtrl = malloc(sizeof(t_material));
                if (!cy->mtrl)
                {
                    printf("Failed to allocate cylinder material\n");
                    return 0 ;
                }
                cy->mtrl->color = *cy->color;
                cy->mtrl->ambient = scene->alight->ratio;
                cy->mtrl->diffuse = 0.5;
                cy->mtrl->specular = 0.5;
                cy->mtrl->shininess = 60;
                render_scene_cy(data->img, scene);
                free(scene->cy->color);
                free(scene->cy->c_axis);
                free(scene->cy->c_cntr);
                free(scene->cy->mtrl);
                scene->cy = scene->cy->next;
            }
        }
        mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
        mlx_key_hook(data->win, ft_escape_key, data);
        mlx_hook(data->win, 17, 0, ft_close, data);
        mlx_loop(data->ptr);
        free(scene->cam->dir);
        free(scene->cam->pos);
        free(scene->cam);
        free(scene->alight->color);
        free(scene->alight);
        free(scene->light->color);
        free(scene->light->dir);
        free(scene->light);
        free(scene);
        return (0);
    }
