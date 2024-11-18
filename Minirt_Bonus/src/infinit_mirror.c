#include "../includes/minirt_bonus.h"

t_ray calculate_reflection_ray(t_ray *incident_ray, t_vctr hit_point, t_vctr normal) {
    t_ray reflection;
    t_vctr reflect_dir;
    
    // R = I - 2(I·N)N where I is incident ray, N is normal
    double dot = vec3_dot(incident_ray->direction, normal);
    reflect_dir = vec3_sub(incident_ray->direction, 
                          vec3_scale(normal, 2.0 * dot));
    
    reflection.origin = hit_point;
    reflection.direction = vec3_normalize(reflect_dir);
    
    return reflection;
}