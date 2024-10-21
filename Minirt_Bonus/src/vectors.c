#include "../includes/minirt_bonus.h"
#include <math.h>

t_vec3 *vec3_add(t_vec3 *v1, t_vec3 *v2)
{
    return vec3_create(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}

t_vec3 *vec3_sub(t_vec3 *v1, t_vec3 *v2)
{
    return vec3_create(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}

t_vec3 *vec3_scale(t_vec3 *v, double t)
{
    return vec3_create(v->x * t, v->y * t, v->z * t);
}

t_vec3 *vec3_cross(t_vec3 *v1, t_vec3 *v2)
{
    return vec3_create(
        v1->y * v2->z - v1->z * v2->y,
        v1->z * v2->x - v1->x * v2->z,
        v1->x * v2->y - v1->y * v2->x
    );
}

double vec3_dot(t_vec3 *v1, t_vec3 *v2)
{
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

t_vec3 *vec3_normalize(t_vec3 *v)
{
    double length = sqrt(vec3_dot(v, v));
    if (length == 0)
        return vec3_create(0, 0, 0);
    return vec3_scale(v, 1 / length);
}
