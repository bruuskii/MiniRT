#include "../includes/minirt_bonus.h"
#include <math.h>

t_vctr vec3_create(double x, double y, double z)
{
    t_vctr vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return (vec);
}

t_ray create_ray(t_cam *cam, double u, double v)
{
    t_ray ray;
    double aspect_ratio = (double)WINDOW_WIDTH / WINDOW_HEIGHT;
    double viewport_height = 2.0 * tan(cam->fov * 0.5 * M_PI / 180.0);
    double viewport_width = aspect_ratio * viewport_height;

    t_vctr w = vec3_normalize(vec3_scale(*(cam->dir), -1));
    t_vctr u_vec = vec3_create(0, 1, 0);
    t_vctr v_vec = vec3_cross(w, u_vec);
    u_vec = vec3_cross(v_vec, w);

    t_vctr horizontal = vec3_scale(v_vec, viewport_width);
    t_vctr vertical = vec3_scale(u_vec, viewport_height);
    t_vctr lower_left_corner = vec3_sub(*(cam->pos), 
                                        vec3_add(vec3_scale(horizontal, 0.5), 
                                                 vec3_add(vec3_scale(vertical, 0.5), w)));
    ray.origin = *(cam->pos);
    ray.direction = vec3_normalize(vec3_sub(vec3_add(lower_left_corner, 
                                                     vec3_add(vec3_scale(horizontal, u), 
                                                              vec3_scale(vertical, v))), 
                                            *(cam->pos)));
    return (ray);
}

t_ray create_shadow_ray(t_hit hit, t_vctr l_pos)
{
    t_ray   s_ray;
    t_vctr  direction;

    direction = vec3_sub(l_pos, hit.point);
    direction = vec3_normalize(direction);
    s_ray.origin = vec3_add(hit.point, vec3_scale(direction, 10));
    s_ray.direction = direction;
    return (s_ray);
}