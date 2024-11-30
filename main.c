/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:38:04 by kbassim           #+#    #+#             */
/*   Updated: 2024/11/29 17:56:30 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

void put_pixel_to_image(char *img_data, int x, int y, int color)
{
    int offset;

    offset = (y * WIDTH + x) * 4;
    *(unsigned int*)(img_data + offset) = color;
}

double dgrs_to_rdn(double angle)
{
    return (angle * (M_PI / 180.0));
}
void convert_3d_to_2d(double x, double y, double z, double d, int *x2, int *y2, double fov)
{
    double aspect_ratio = (double)WIDTH / HEIGHT;
    double scale = tan(fov / 2.0) * 2.0;
    
    if (z <= 0)
    {
        *x2 = *y2 = -1;
        return;
    }
    double proj_x = (x / z) * d * scale * aspect_ratio;
    double proj_y = (y / z) * d * scale;
    *x2 = (int)(proj_x + (WIDTH / 2));
    *y2 = (int)(proj_y + (HEIGHT / 2));
}



double calculate_distance(double fov)
{
    double d;
    double fv;

    fv = dgrs_to_rdn(fov);
    d = WIDTH / (2 * tan(fv / 2.0));
    return (d);
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
    //t_vctr color;
    char *img_data;
    int bits_per_pixel, size_line, endian;

    img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    sp = (t_sp *)scene->sp;
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            double u = ((double)x / (WIDTH - 1));
            double v = ((double)y / (HEIGHT - 1));
            ray = create_ray(scene->cam, u, v);
            hit = intersect_sphere(&ray, scene->sp);
            if (hit && hit->hit)
            {
                t_vctr final_color = {0, 0, 0};
                t_light *light = scene->light;
                while (light)
                {
                    t_vctr light_color = calculate_lighting(&ray, *hit, hit->normal, scene, sp->mtrl, light, u, v);
                    final_color.x += light_color.x;
                    final_color.y += light_color.y;
                    final_color.z += light_color.z;
                    if (light)
                        light = light->next;
                }
                final_color.x = fmin(fmax(final_color.x, 0), 255);
                final_color.y = fmin(fmax(final_color.y, 0), 255);
                final_color.z = fmin(fmax(final_color.z, 0), 255);
                put_pixel_to_image(img_data, x, y, create_trgb(0, (int)final_color.x, (int)final_color.y, (int)final_color.z));
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
    t_hit *hit;
    char *img_data;
    int bits_per_pixel, size_line, endian;
    double d;

    img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    y = 0;
    d = calculate_distance(scene->cam->fov);
    while (y < HEIGHT) 
    {
        x = 0;
        while (x < WIDTH) 
        {
            double u = ((double)x / (WIDTH - 1));
            double v = ((double)y / (HEIGHT - 1));
            ray = create_ray(scene->cam, u, v);
            hit = intersect_plane(&ray, scene->pl, d);
            if (hit && hit->hit) 
            {
                t_vctr final_color = {0, 0, 0};
                t_light *light = scene->light;
                while (light) 
                {
                    t_vctr light_color = calculate_lighting(&ray, *hit, hit->normal, scene, scene->pl->mtrl, light, u, v);
                    final_color.x += light_color.x;
                    final_color.y += light_color.y;
                    final_color.z += light_color.z;
                    light = light->next;
                }
                final_color.x = fmin(fmax(final_color.x, 0), 255);
                final_color.y = fmin(fmax(final_color.y, 0), 255);
                final_color.z = fmin(fmax(final_color.z, 0), 255);
                 put_pixel_to_image(img_data, x, y, create_trgb(0, (int)final_color.x, (int)final_color.y, (int)final_color.z));
            }
            free(hit);
            x++;
        }
        y++;
    }
}



// void render_scene_cy(void *img, t_scene *scene)
// {
//     int x, y;
//     t_ray ray;
//     t_cylinder *cy;
//     t_hit *hit;
//     t_vctr color;
//     char *img_data;
//     int bits_per_pixel, size_line, endian;

//     img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
//     cy = (t_cylinder *)scene->cy;
//     y = 0;
//     while (y < HEIGHT)
//     {
//         x = 0;
//         while (x < WIDTH)
//         {
//             double u = ((double)x / (WIDTH - 1));
//             double v = ((double)y / (HEIGHT - 1));
//             ray = create_ray(scene->cam, u, v);
//             hit = intersect_cylinder(&ray, cy);
//             if (hit->hit)
//             {
//                 color = calculate_lighting(&ray, hit->point, hit->normal, scene, cy->mtrl);
//                 put_pixel_to_image(img_data, x, y, create_trgb(0, (int)(color.x), (int)(color.y), (int)(color.z)));
//             }
//             free(hit);
//             x++;
//         }
//         y++;
//     }
// }

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
    data->win = mlx_new_window(data->ptr, WIDTH, HEIGHT, "miniRT Bonus");
    if (!data->win)
    {
        mlx_destroy_display(data->ptr);
        free(data->ptr);
        return (1);
    }
    scene =  data_input(av[1]);
    printf("light x ==  %f\n", scene->light->dir->x);
    data->img = mlx_new_image(data->ptr, WIDTH, HEIGHT);
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
            free(scene->sp);
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
            //render_scene_cy(data->img, scene);
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
