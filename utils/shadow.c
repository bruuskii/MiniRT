/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:26:43 by kbassim           #+#    #+#             */
/*   Updated: 2024/12/01 20:48:04 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_ray create_nray(t_vctr point, t_vctr dir, double u, double v)
{
    t_ray ray;
    double aspect_ratio = (double)WIDTH / HEIGHT;
    double viewport_height = 2.0 * tan(45.0 * 0.5 * M_PI / 180.0);
    double viewport_width = aspect_ratio * viewport_height;

    t_vctr w = vec3_normalize(vec3_scale(dir, -1));
    t_vctr u_vec = vec3_create(0, 1, 0);
    t_vctr v_vec = vec3_cross(w, u_vec);
    u_vec = vec3_cross(v_vec, w);

    t_vctr horizontal = vec3_scale(v_vec, viewport_width);
    t_vctr vertical = vec3_scale(u_vec, viewport_height);
    t_vctr lower_left_corner = vec3_sub(point, 
                                        vec3_add(vec3_scale(horizontal, 0.5), 
                                                 vec3_add(vec3_scale(vertical, 0.5), w)));
    ray.origin = point;
    ray.direction = vec3_normalize(vec3_sub(vec3_add(lower_left_corner, 
                                                     vec3_add(vec3_scale(horizontal, u), 
                                                              vec3_scale(vertical, v))), 
                                            point));
    return (ray);
}

int ft_is_shadowed(t_scene *scene, t_vctr *point, double u, double v)
{
    double  distance;
    t_vctr  vc;
    t_hit   *hit;
    t_ray   ray;
    t_vctr  dir;

    vc = vec3_sub(*scene->light->dir, *point);       
    distance = ft_magnitude(&vc);                                             
    dir = vec3_normalize(vc);
    ray = create_nray(*point, dir, u, v);            
    hit = intersect_sphere(&ray, scene->sp);          
    if (hit && hit->t < distance)                     
    {
        free(hit);
        return 1;                                     
    }
    free(hit);
    return 0;                                        
}
