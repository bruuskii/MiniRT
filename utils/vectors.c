
#include "../miniRT.h"

t_vctr  *ft_verctor(float x, float y, float z)
{
    t_vctr  *vector;

    vector = malloc(sizeof(t_vctr));
    if (!vector)
        return (NULL);
    vector->x = x;
    vector->y = y;
    vector->z = z;
    return (vector);
}

double  ft_magnitude(t_vctr *vec)
{
    return (sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z)));
}

t_vctr    *vct_norm(t_vctr *vec)
{
    double  magnitude;

    if (!vec)
        return (NULL);
    magnitude = ft_magnitude(vec);
    if (magnitude == 0)
        return (NULL);
    vec->x = vec->x / magnitude;
    vec->y = vec->y / magnitude;
    vec->z = vec->z / magnitude;
    return (vec);
}
