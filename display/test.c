/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:06:58 by kbassim           #+#    #+#             */
/*   Updated: 2024/10/11 22:01:11 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int ft_color()
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    double a;

    r = 255;
    g = 0;
    b = 0;
    a = 0.1;
    unsigned char alpha = (unsigned char)(a * 255.0);
    return (alpha << 24 | r << 16 | g << 8 | b);
}

double dgrs_to_rdn(double angle)
{
    return (angle * (M_PI / 180.0));
}

double calculate_distance(double fov)
{
    double d;
    double fv;

    if (fov == 0)
        return (-1);
    fv = dgrs_to_rdn(fov);
    d = WIDTH / (2 * tan(fv / 2.0));
    return (d);
}

void convert_3d_to_2d(double x, double y, double z, double d, int *x2, int *y2)
{
    *x2 = (int)((x * d) / (z + d)) + WIDTH / 2;
    *y2 = (int)((y * d) / (z + d)) + HEIGHT / 2;
}

void ft_display_sphere(t_win *w, t_cam *cam, t_sp *sp)
{
    char *pix;
    char *data;
    int sl = 0;
    int endn;
    int bpp = 32;
    double theta, phi;
    double x, y, z;
    int x2, y2;
    double radius = (sp->d  / 2) * 8;
    printf("radius == %f\n", radius);
    double d = calculate_distance(cam->fov);

    data = mlx_get_data_addr(w->img, &bpp, &sl, &endn);
    theta = 0;
    while (theta <= M_PI)
    {
        phi = 0;
        while (phi <= 2 * M_PI)
        {
            x = radius * sin(theta) * cos(phi) + sp->cntr->x;
            y = radius * cos(theta) + sp->cntr->y;
            z = radius * sin(theta) * sin(phi) + sp->cntr->z;
            convert_3d_to_2d(x, y, z, d, &x2, &y2);
            if (x2 >= 0 && x2 < WIDTH && y2 >= 0 && y2 < HEIGHT)
            {
                pix = data + (x2 * (bpp / 8) + y2 * sl);
                *(int *)pix = sp->color->r << 16 | sp->color->g << 8 | sp->color->b;
            }
            phi += 0.01;
        }
        theta += 0.01;
    }
}

double gyroid(double x, double y, double z) 
{
    return sin(x) * cos(y) + sin(y) * cos(z) + sin(z) * cos(x);
}

void ft_display_plane(t_win *w) 
{
    char *pix;
    char *data;
    int sl = 0;
    int endn;
    int bpp;
    double x, y, z;
    int x2, y2;
    double d = calculate_distance(60);
    double point_on_plane[3] = {1.0, 1.0, 1.0};
    double normal_vector[3] = {1.0, 1.0, -1.0};

    data = mlx_get_data_addr(w->img, &bpp, &sl, &endn);
    x = -1.0;
    while (x <= 1.0)
    {
        y = -1.0;
        while (y <= 1) 
        {
            if (fabs(normal_vector[2]) > 1e-3)
            {
                z = (normal_vector[0] * (x - point_on_plane[0]) +
                     normal_vector[1] * (y - point_on_plane[1])) / 
                     normal_vector[2] + point_on_plane[2];
            } 
            else 
                z = point_on_plane[2];
            convert_3d_to_2d(x * 400, y * 400 , z * 400 , d, &x2, &y2);
            if (x2 >= 0 && x2 < WIDTH && y2 >= 0 && y2 < HEIGHT) 
            {
                pix = data + (x2 * (bpp / 8) + y2 * sl);
                *(int *)pix = 0xFFFFFF;
            }
            y += 0.001;
        }
        x += 0.001;
    } 
}

void ft_display(t_win *w, t_scene *scene) 
{
    while (scene->obj)
    {
        if (scene->obj->type == SPHERE)
            ft_display_sphere(w, scene->cam, ((t_sp *)(scene->obj->obj)));
        scene->obj = scene->obj->next;
    }
    //ft_display_plane(w);
    mlx_put_image_to_window(w->ptr, w->win, w->img, 0, 0);
}
