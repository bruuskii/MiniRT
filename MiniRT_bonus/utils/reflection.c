/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:16:54 by kbassim           #+#    #+#             */
/*   Updated: 2024/12/26 22:07:05 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vctr  vec3_multi(t_vctr v1, t_vctr v2)
{
    return (vec3_create(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}

t_ray   *reflected_ray(t_hit *hit, t_ray *ray)
{
    t_vctr  normal;
    t_vctr  reflection_dir;
    t_ray   *reflect_ray;
    double  vctr_dot;

    if (!hit || !ray)
        return (NULL);
    reflect_ray = malloc(sizeof(t_ray));
    if (!reflect_ray)
        return (NULL);
    normal = hit->normal;
    vctr_dot = 2 * vec3_dot(vec3_normalize(ray->direction), normal);
    reflection_dir = vec3_sub(ray->direction, vec3_scale(normal, vctr_dot));
    reflect_ray->direction = vec3_normalize(reflection_dir);
    reflect_ray->origin = vec3_add(hit->point, vec3_scale(normal, 1e-6));
    return (reflect_ray);
}