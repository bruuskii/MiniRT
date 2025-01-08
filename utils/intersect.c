#include "../miniRT.h"


double  ft_magnitude(t_vctr *vec)
{
    return (sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z)));
}
t_hit *intersect_sphere(t_ray *ray, t_sp *sphere)
{
    t_hit *hit = malloc(sizeof(t_hit));
    t_vctr oc = vec3_sub(ray->origin, *sphere->cntr);
    double a = vec3_dot(ray->direction, ray->direction);
    double r = sphere->d / 2;
    double b = 2.0 * vec3_dot(oc, ray->direction);
    double c = vec3_dot(oc, oc) - r * r;
    double discriminant = b * b - 4 * a * c;
    hit->t = 0;
    if (discriminant < 0)
    {
        hit->hit = 0;
        return hit;
    }
    hit->shaddow = discriminant ? 1.0 : 0.0;
    double sqrt_discriminant = sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2.0 * a);
    double t2 = (-b + sqrt_discriminant) / (2.0 * a);
    
    if (t1 > 1e-6)
        hit->t = t1;
    else if (t2 > 1e-6)
        hit->t = t2;
    else 
        return (hit);
    
    hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
    t_vctr original_normal = vec3_normalize(vec3_sub(hit->point, *sphere->cntr));
    
    if (sphere->fl == 1)
    {
        double bump_intensity = 0.1;
        double noise_x = fmod(sin(hit->point.x * 10), 1.0);
        double noise_y = fmod(cos(hit->point.y * 10), 1.0);
        double noise_z = fmod(tan(hit->point.z * 10), 1.0); 
        t_vctr noise_offset = {
            noise_x * bump_intensity,
            noise_y * bump_intensity,
            noise_z * bump_intensity
        };
        hit->normal = vec3_normalize(vec3_add(original_normal, noise_offset));
    }
    else
        hit->normal = original_normal;
    return (hit);
}


t_hit *intersect_plane(t_ray *ray, t_plane *plane)
{
    t_hit *hit = malloc(sizeof(t_hit));
    if (!hit)
        return NULL;
    
    // Initialize hit structure
    hit->hit = 0;
    hit->t = INFINITY;
    
    // Normalize direction vectors
    t_vctr D = vec3_normalize(ray->direction);
    t_vctr N = vec3_normalize(*plane->normal);
    
    // Calculate denominator (D·N)
    double denom = vec3_dot(D, N);
    
    // Check if ray is parallel to plane (or nearly parallel)
    // Using a slightly larger epsilon for better numerical stability
    const double EPSILON = 1e-7;
    if (fabs(denom) < EPSILON)
        return hit;
    
    // Calculate vector from ray origin to plane point
    t_vctr ray_to_plane = vec3_sub(*plane->point, ray->origin);
    
    // Calculate intersection distance
    double t = vec3_dot(ray_to_plane, N) / denom;
    
    // Check if intersection is behind the ray
    if (t < EPSILON)
        return hit;
    
    // Calculate intersection point
    t_vctr intersection = vec3_add(ray->origin, vec3_scale(D, t));
    
    // Calculate plane basis vectors for UV mapping
    t_vctr plane_u, plane_v;
    
    // Choose most stable axis for cross product
    t_vctr up = (fabs(N.y) < 0.9) ? (t_vctr){0, 1, 0} : (t_vctr){0, 0, 1};
    plane_u = vec3_normalize(vec3_cross(N, up));
    plane_v = vec3_normalize(vec3_cross(N, plane_u));
    
    // Calculate UV coordinates
    t_vctr local_point = vec3_sub(intersection, *plane->point);
    double u = vec3_dot(local_point, plane_u);
    double v = vec3_dot(local_point, plane_v);
    
    // Check if point is within plane bounds
    // Using fixed dimensions as in original code
    const double MAX_WIDTH = 110.0;   // From original code
    const double MAX_HEIGHT = 120.0;  // From original code
    if (fabs(u) > MAX_WIDTH || fabs(v) > MAX_HEIGHT)
        return hit;
    
    // Fill hit information
    hit->hit = 1;
    hit->t = t;
    hit->point = intersection;
    hit->normal = (denom < 0) ? N : vec3_scale(N, -1); // Ensure normal faces ray
    
    return hit;
}



t_hit *intersect_cylinder(t_ray *ray, t_cylinder *cy)
{
    t_hit *hit = malloc(sizeof(t_hit));

    if (!hit) 
        return NULL;
    hit->hit = 0;
    hit->t = 0;
    t_vctr oc = vec3_sub(ray->origin, *cy->c_cntr);
    double a = vec3_dot(ray->direction, ray->direction) - pow(vec3_dot(ray->direction, *cy->c_axis), 2);
    double b = 2 * (vec3_dot(ray->direction, oc) - vec3_dot(ray->direction, *cy->c_axis) * vec3_dot(oc, *cy->c_axis));
    double c = vec3_dot(oc, oc) - pow(vec3_dot(oc, *cy->c_axis), 2) - pow(cy->d / 2, 2);
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return hit;
    double sqrt_discriminant = sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2 * a);
    double t2 = (-b + sqrt_discriminant) / (2 * a);
    double t = -1;
    if (t1 > 1e-6)
        t = t1;
    else if (t2 > 1e-6)
        t = t2;
    else 
        return (hit);
    hit->t = t;
    hit->hit = 1;
    hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
    t_vctr projection = vec3_scale(*cy->c_axis, vec3_dot(vec3_sub(hit->point, *cy->c_cntr), *cy->c_axis));
    t_vctr proj_point = vec3_add(*cy->c_cntr, projection);
    t_vctr vctr = vec3_sub(proj_point, *cy->c_cntr);
    double distance = ft_magnitude(&vctr);
    if (distance > cy->height )
    {
        hit->hit = 0;
        return hit;
    }
    hit->normal = vec3_normalize(vec3_sub(hit->point, proj_point));
    return hit;
}

t_hit *intersect_cone(t_ray *ray, t_cone *cone)
{
    if (!ray || !cone)
        return NULL;

    t_hit *hit = malloc(sizeof(t_hit));
    if (!hit)
        return NULL;

    t_vctr CO = vec3_sub(ray->origin, *(cone->vertex));
    t_vctr D = ray->direction;
    t_vctr V = vec3_normalize(*(cone->axis));
    double k = tan(cone->tang * M_PI / 180.0);

    double D_dot_V = vec3_dot(D, V);
    double CO_dot_V = vec3_dot(CO, V);
    double D_dot_D = vec3_dot(D, D);
    double CO_dot_D = vec3_dot(CO, D);
    double CO_dot_CO = vec3_dot(CO, CO);

    double a = D_dot_D - (1.0 + k * k) * D_dot_V * D_dot_V;
    double b = 2.0 * (CO_dot_D - (1.0 + k * k) * D_dot_V * CO_dot_V);
    double c = CO_dot_CO - (1.0 + k * k) * CO_dot_V * CO_dot_V;
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0 || fabs(a) < 1e-6) {
        free(hit);
        return NULL;
    }
    double sqrt_discriminant = sqrt(discriminant);
    double t0 = (-b - sqrt_discriminant) / (2.0 * a);
    double t1 = (-b + sqrt_discriminant) / (2.0 * a);
    double t;
    if (t0 > 1e-6 && t1 > 1e-6)
        t = fmin(t0, t1);
    else if (t0 > 1e-6)
        t = t0;
    else if (t1 > 1e-6)
        t = t1;
    else {
        free(hit);
        return NULL;
    }
    t_vctr intersection_point = vec3_add(ray->origin, vec3_scale(D, t));
    t_vctr hit_to_vertex = vec3_sub(intersection_point, *(cone->vertex));
    double m = vec3_dot(hit_to_vertex, V);
    if (m < cone->minm || m > cone->maxm) 
    {
        free(hit);
        return NULL;
    }
    t_vctr normal = vec3_sub(hit_to_vertex, vec3_scale(V, m));
    normal = vec3_normalize(normal);
    hit->t = t;
    hit->hit = 1;
    hit->point = intersection_point;
    hit->normal = normal;

    return hit;
}
