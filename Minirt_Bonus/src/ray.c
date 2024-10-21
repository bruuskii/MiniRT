#include "../includes/minirt_bonus.h"
#include <math.h>

t_vec3 *vec3_create(double x, double y, double z)
{
    t_vec3 *vec;

    vec = malloc(sizeof(t_vec3));
    if (!vec)
        return (NULL);
    vec->x = x;
    vec->y = y;
    vec->z = z;
    return (vec);
}

t_ray *create_ray(t_camera *camera, double u, double v)
{
    t_ray *ray;

    ray = malloc(sizeof(t_ray));
    if (!ray)
        return (NULL);
    double aspect_ratio = (double)WINDOW_WIDTH / WINDOW_HEIGHT;
    double viewport_height = 2.0 * tan(camera->fov * 0.5 * M_PI / 180.0);
    double viewport_width = aspect_ratio * viewport_height;

    t_vec3 *w = vec3_normalize(vec3_scale(camera->direction, -1));
    t_vec3 *u_vec = vec3_create(0, 1, 0); // Assuming 'up' is (0,1,0)
    t_vec3 *v_vec = vec3_cross(w, u_vec);
    u_vec = vec3_cross(v_vec, w);

    t_vec3 *horizontal = vec3_scale(v_vec, viewport_width);
    t_vec3 *vertical = vec3_scale(u_vec, viewport_height);
    t_vec3 *lower_left_corner = vec3_sub(camera->position, 
                                        vec3_add(vec3_scale(horizontal, 0.5), 
                                                 vec3_add(vec3_scale(vertical, 0.5), w)));

    ray->origin = camera->position;
    ray->direction = vec3_normalize(vec3_sub(vec3_add(lower_left_corner, 
                                                     vec3_add(vec3_scale(horizontal, u), 
                                                              vec3_scale(vertical, v))), 
                                            camera->position));
    return (ray);
}