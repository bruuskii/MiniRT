#include "../includes/minirt_bonus.h"

t_hit *intersect_sphere(t_ray *ray, t_sphere *sphere)
{
    t_hit *hit = malloc(sizeof(t_hit));
    if (!hit) {
        // Handle memory allocation failure
        return NULL; // Or handle it appropriately
    }

    // Initialize hit fields
    hit->hit = 0;
    hit->t = 0;
    hit->point = &(t_vec3){0, 0, 0}; // Using compound literal
    hit->normal = &(t_vec3){0, 0, 0}; // Using compound literal
    t_vec3 *oc = vec3_sub(ray->origin, sphere->center);
    double a = vec3_dot(ray->direction, ray->direction);
    double b = 2.0 * vec3_dot(oc, ray->direction);
    double c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return hit;
    double sqrt_discriminant = sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2.0 * a);
    double t2 = (-b + sqrt_discriminant) / (2.0 * a);

    if (t1 > 0.001)
        hit->t = t1;
    else if (t2 > 0.001)
        hit->t = t2;
    else
        return hit;

    hit->hit = 1;
    hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
    hit->normal = vec3_normalize(vec3_sub(hit->point, sphere->center));
    return hit;
}