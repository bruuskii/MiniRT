#include "../includes/minirt_bonus.h"

t_hit *intersect_sphere(t_ray *ray, t_sp *sphere)
{
    t_hit *hit = malloc(sizeof(t_hit));
    t_vctr oc = vec3_sub(ray->origin, *sphere->cntr);
    //printf("oc %f\n", oc.x);
    double a = vec3_dot(ray->direction, ray->direction);
    //printf("a == %f\n",a);
    double b = 2.0 * vec3_dot(oc, ray->direction);
    //printf("b == %f\n",b);
    double c = vec3_dot(oc, oc) - (sphere->d / 2) * (sphere->d / 2);
    //printf("c == %f\n",c);
    double discriminant = b * b - 4 * a * c;
    //printf("descriminant %f\n", discriminant);
    // if (discriminant >= 0)
    // {
    //     //printf("sdfghjkl\n");
    //     //exit(0);
    // }
    // printf("ray->origin->x == %f && ray->origin->y == %f && ray->origin->z == %f\n", ray->origin.x, ray->origin.y, ray->origin.z);
    // printf("ray->direction->x == %f && ray->direction->y == %f && ray->direction->z == %f\n", ray->direction.x, ray->direction.y, ray->direction.z);
    // printf("sp->cntr->x == %f && sp->cntr->y == %f && sp->cntr->z == %f\n", sphere->cntr->x, sphere->cntr->y, sphere->cntr->z);
    // printf("sp->d %f\n", sphere->d);   
    // exit (0);
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
    hit->normal = vec3_normalize(vec3_sub(hit->point, *sphere->cntr));
    return hit;
}