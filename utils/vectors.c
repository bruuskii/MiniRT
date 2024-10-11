/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:07:28 by kbassim           #+#    #+#             */
/*   Updated: 2024/10/06 22:07:59 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_vctr    *vct_sub(t_vctr *v1, t_vctr *v2)
{
    t_vctr *v;

    v->x = v1->x - v2->x;
    v->y = v1->y - v2->y;
    v->z = v1->z - v2->z;
    return (v);
}
