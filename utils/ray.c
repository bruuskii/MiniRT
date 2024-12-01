#include "../miniRT.h"

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
    double aspect_ratio = (double)WIDTH / HEIGHT;
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

t_ray create_shadow_ray(t_hit hit, t_vctr point, t_light *light)
{
    t_vctr  vec;
    t_ray   s_ray;
    t_vctr  normal;
    t_vctr  light_dir;
    t_vctr  biased;

    vec = vec3_sub(hit.point, point);
    normal = vec3_normalize(vec);
    biased = vec3_add(vec3_scale(normal, 1e-6), hit.point);
    light_dir = vec3_sub(*light->dir, biased);
    s_ray.origin = biased;
    s_ray.direction = vec3_normalize(light_dir);

    return (s_ray);
}