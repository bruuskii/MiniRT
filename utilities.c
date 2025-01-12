#include "miniRT.h"

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}


void ft_free_all(t_scene **scene)
{
    t_sp        *sp;
    t_sp        *sp_next;
    t_cylinder  *cy;
    t_cylinder  *cy_next;
    t_plane     *pl;
    t_plane     *pl_next;
    t_light     *lt;
    t_light     *lt_next;
    t_cone      *cn;
    t_cone      *cn_next;

    if (!scene || !*scene)
        return;
    if ((*scene)->cam)
    {
        free((*scene)->cam->dir);
        free((*scene)->cam->pos);
        free((*scene)->cam);
    }
    sp = (*scene)->sp;
    while (sp)
    {
        sp_next = sp->next;
        free(sp->cntr);
        free(sp->color);
        if (sp->mtrl)
            free(sp->mtrl);
        sp = sp_next;
    }
    pl = (*scene)->pl;
    while (pl)
    {
        pl_next = pl->next;
        free(pl->point);
        free(pl->normal);
        free(pl->color);
        if (pl->mtrl)
            free(pl->mtrl);
        free(pl);
        pl = pl_next;
    }
    cy = (*scene)->cy;
    while (cy)
    {
        cy_next = cy->next;
        free(cy->c_axis);
        free(cy->c_cntr);
        free(cy->color);
        if (cy->mtrl)
            free(cy->mtrl);
        free(cy);
        cy = cy_next;
    }
    lt = (*scene)->light;
    while (lt)
    {
        lt_next = lt->next;
        free(lt->color);
        free(lt->dir);
        free(lt);
        lt = lt_next;
    }
    if ((*scene)->alight)
    {
        free((*scene)->alight->color);
        free((*scene)->alight);
    }
    cn = (*scene)->cn;
    while (cn)
    {
        cn_next = cn->next;
        free(cn->vertex);
        free(cn->axis);
        free(cn->color);
        if (cn->mtrl)
            free(cn->mtrl);
        free(cn);
        cn = cn_next;
    }
}



void put_pixel_to_image(char *img_data, int x, int y, int color)
{
    int offset;

    offset = ((HEIGHT - 1 - y) * WIDTH + x) * 4;
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
    int     x, y;
    t_ray   *ray;
    t_sp    *sp;
    t_hit   *hit;
    char    *img_data;
    int     bits_per_pixel, size_line, endian;

    img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    sp = (t_sp *)scene->sp;
    y = 0;
    if (!scene)
        return ;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            double u = ((double)x / (WIDTH - 1));
            double v = ((double)y / (HEIGHT - 1));
            ray = create_ray(scene->cam, u, v);
            hit = intersect_sphere(ray, scene->sp);
            hit->type = SPHERE;
            if (!ray)
                return ;
            if (hit && hit->hit)
            {
                t_vctr final_color = {0, 0, 0};
                t_light *light = scene->light;
                while (light)
                {
                    t_vctr light_color = calculate_lighting(ray, *hit, hit->normal, scene, sp->mtrl, light, u, v);
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
            free(ray);
            x++;
        }
        y++;
    }
}


void render_scene_cn(void *img, t_scene *scene)
{
    int     x, y;
    t_ray   *ray;
    t_cone    *sp;
    t_hit   *hit;
    char    *img_data;
    int     bits_per_pixel, size_line, endian;

    img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    sp = (t_cone *)scene->cn;
    y = 0;
    if (!scene)
        return ;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            double u = ((double)x / (WIDTH - 1));
            double v = ((double)y / (HEIGHT - 1));
            ray = create_ray(scene->cam, u, v);
            hit = intersect_cone(ray, scene->cn);
            //hit->type = CONE;
            if (hit && hit->hit)
            {
                t_vctr final_color = {0, 0, 0};
                t_light *light = scene->light;
                while (light)
                {
                    t_vctr light_color = calculate_lighting(ray, *hit, hit->normal, scene, sp->mtrl, light, u, v);
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
            free(ray);
            x++;
        }
        y++;
    }
    
}

void render_scene_plane(void *img, t_scene *scene) 
{
    int x, y;
    t_ray *ray;
    t_hit *hit;
    char *img_data;
    int bits_per_pixel, size_line, endian;

    img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    y = 0;
    while (y < HEIGHT) 
    {
        x = 0;
        while (x < WIDTH) 
        {
            double u = ((double)x / (WIDTH - 1));
            double v = ((double)y / (HEIGHT - 1));
            ray = create_ray(scene->cam, u, v);
            if (!ray)
                return ;
            hit = intersect_plane(ray, scene->pl);
            hit->type = PLANE;
            if (hit && hit->hit) 
            {
                t_vctr final_color = {0, 0, 0};
                t_light *light = scene->light;
                while (light) 
                {
                    t_vctr light_color = calculate_lighting(ray, *hit, hit->normal, scene, scene->pl->mtrl, light, u, v);
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
            free(ray);
            x++;
        }
        y++;
    }
}

void render_scene_cy(void *img, t_scene *scene) 
{
    int x, y;
    t_ray *ray;
    t_hit *hit;
    char *img_data;
    int bits_per_pixel, size_line, endian;

    img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    y = 0;
    while (y < HEIGHT) 
    {
        x = 0;
        while (x < WIDTH) 
        {
            double u = ((double)x / (WIDTH - 1));
            double v = ((double)y / (HEIGHT - 1));
            ray = create_ray(scene->cam, u, v);
            if (ray == 0)
                return ;
            hit = intersect_cylinder(ray, scene->cy);
            hit->type = CYLINDRE;
            if (hit && hit->hit) 
            {
                t_vctr final_color = {0, 0, 0};
                t_light *light = scene->light;
                while (light) 
                {
                    t_vctr light_color = calculate_lighting(ray, *hit, hit->normal, scene, scene->cy->mtrl, light, u, v);
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
            free(ray);
            free(hit);
            x++;
        }
        y++;
    }
}
