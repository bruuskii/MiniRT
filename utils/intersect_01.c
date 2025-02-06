/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:05:25 by izouine           #+#    #+#             */
/*   Updated: 2025/02/06 07:28:38 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_hit	*ft_hit(void)
{
	t_hit	*hit_point;

	hit_point = malloc(sizeof(t_hit));
	if (!hit_point)
		return (printf("hit point non-allocated"), NULL);
	hit_point->hit = 0;
	hit_point->t = 0;
	hit_point->mtrl = malloc(sizeof(t_material));
	if (!hit_point->mtrl)
		return (free(hit_point), printf("hit point non-allocated"), NULL);
	hit_point->mtrl->diffuse = 0.6;
	hit_point->mtrl->specular = 0.6;
	hit_point->mtrl->shininess = 60;
	return (hit_point);
}

double	ft_calculate_discriminant_sphere(t_ray *ray, t_sp *sphere)
{
	t_vctr	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_sub(*ray->origin, *sphere->cntr);
	a = vec3_dot(*ray->direction, *ray->direction);
	b = 2.0 * vec3_dot(oc, *ray->direction);
	c = vec3_dot(oc, oc) - (sphere->d / 2) * (sphere->d / 2);
	discriminant = b * b - 4 * a * c;
	return (discriminant);
}

int	ft_assign_t(t_hit *hit, t_ray *ray, double discriminant, t_sp *sphere)
{
	double	a;
	double	b;
	double	t1;
	double	t2;
	t_vctr	oc;

	oc = vec3_sub(*ray->origin, *sphere->cntr);
	a = vec3_dot(*ray->direction, *ray->direction);
	b = 2.0 * vec3_dot(oc, *ray->direction);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > 1e-6)
	{
		hit->t = t1;
		hit->hit = 1;
		return (0);
	}
	else if (t2 > 1e-6)
	{
		hit->t = t2;
		hit->hit = 1;
		return (0);
	}
	return (1);
}

t_hit	*intersect_sphere(t_ray *ray, t_sp *sphere)
{
	t_hit	*hit;
	t_vctr	original_normal;
	double	discriminant;

	hit = ft_hit();
	discriminant = ft_calculate_discriminant_sphere(ray, sphere);
	if (discriminant < 0)
	{
		hit->hit = 0;
		free(hit->mtrl);
		free(hit);
		return (NULL);
	}
	if (ft_assign_t(hit, ray, discriminant, sphere))
		return (free(hit->mtrl), free(hit), NULL);
	hit->point = vec3_add(*ray->origin, vec3_scale(*ray->direction, hit->t));
	original_normal = vec3_normalize(vec3_sub(hit->point, *sphere->cntr));
	if (sphere->fl == 1)
		ft_checker(hit, original_normal);
	else
		hit->normal = original_normal;
	return (hit);
}
