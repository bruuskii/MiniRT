#include "../miniRT.h"

double	ft_magnitude(t_vctr *vec)
{
	return (sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z)));
}

t_hit	*ft_hit(void)
{
	t_hit	*hit_point;

	hit_point = malloc(sizeof(t_hit));
	if (!hit_point)
		return (printf("hit point non-allocated"), NULL);
	hit_point->hit = 0;
	hit_point->t = 0;
	return (hit_point);
}

double	ft_calculate_discriminant_sphere(t_ray *ray, t_sp *sphere)
{
	t_vctr	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_sub(ray->origin, *sphere->cntr);
	a = vec3_dot(ray->direction, ray->direction);
	b = 2.0 * vec3_dot(oc, ray->direction);
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

	oc = vec3_sub(ray->origin, *sphere->cntr);
	a = vec3_dot(ray->direction, ray->direction);
	b = 2.0 * vec3_dot(oc, ray->direction);
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
		return (hit);
	}
	if (ft_assign_t(hit, ray, discriminant, sphere))
		return (hit);
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	original_normal = vec3_normalize(vec3_sub(hit->point, *sphere->cntr));
	if (sphere->fl == 1)
		ft_checker(hit, original_normal);
	else
		hit->normal = original_normal;
	return (hit);
}

void	ft_get_plane_axes(t_vctr *plane_u, t_vctr *plane_v, t_vctr *normal)
{
	t_vctr	up;

	if (fabs(normal->z) > 0.9)
	{
		*plane_u = (t_vctr){1, 0, 0};
		*plane_v = (t_vctr){0, 1, 0};
	}
	else
	{
		if (fabs(normal->y) < 0.9)
			up = (t_vctr){0, 1, 0};
		else
			up = (t_vctr){0, 0, 1};
		*plane_u = vec3_normalize(vec3_cross(*normal, up));
		*plane_v = vec3_normalize(vec3_cross(*normal, *plane_u));
	}
}

void	ft_calculate_local_point(
	t_vctr intersection, t_plane *plane, t_vctr plane_u, t_vctr plane_v, double *u, double *v)
{
	t_vctr	local_point;

	local_point = vec3_sub(intersection, *plane->point);
	*u = vec3_dot(local_point, plane_u);
	*v = vec3_dot(local_point, plane_v);
}

int	ft_resize_plane_00(t_vctr intersection, t_plane *plane)
{
	t_vctr	plane_u;
	t_vctr	plane_v;
	double	u;
	double	v;

	ft_get_plane_axes(&plane_u, &plane_v, plane->normal);
	ft_calculate_local_point(intersection, plane, plane_u, plane_v, &u, &v);
	if (fabs(u) > M_W || (fabs(v) >= M_H || fabs(v) <= M_H_00))
		return (1);
	return (0);
}


t_vctr	ft_calculate_intersection_plane(t_vctr denom, t_plane *plane, double t,
		t_ray *ray)
{
	t_vctr	intersection;

	intersection = vec3_add(ray->origin, vec3_scale(denom, t));
	if (!plane->normal->z)
		if (ft_resize_plane_00(intersection, plane))
			return ((t_vctr){0, 0, 0});
	return (intersection);
}

void	ft_assign_hit_plane(t_hit *hit, t_ray *ray, t_plane *plane, double t)
{
	double	den;
	t_vctr	denom;

	denom = vec3_normalize(ray->direction);
	den = vec3_dot(denom, *plane->normal);
	hit->hit = 1;
	hit->t = t;
	hit->point = ft_calculate_intersection_plane(denom, plane, hit->t, ray);
	if (den < 0)
		hit->normal = *plane->normal;
	else
		hit->normal = vec3_scale(*plane->normal, -1);
}

int	is_zero_vector(t_vctr v)
{
	return (v.x == 0 && v.y == 0 && v.z == 0);
}

t_hit	*intersect_plane(t_ray *ray, t_plane *plane)
{
	t_hit	*hit;
	t_vctr	denom;
	double	den;
	t_vctr	ray_to_plane;
	double	t;

	hit = ft_hit();
	if (!hit)
		return (NULL);
	hit->hit = 0;
	hit->t = 0;
	denom = vec3_normalize(ray->direction);
	den = vec3_dot(denom, *plane->normal);
	if (fabs(den) < 1e-6)
		return (hit);
	ray_to_plane = vec3_sub(*plane->point, ray->origin);
	t = vec3_dot(ray_to_plane, *plane->normal) / den;
	if (t < 1e-6)
		return (hit);
	if (is_zero_vector(ft_calculate_intersection_plane(denom, plane, t, ray)))
		return (hit);
	ft_assign_hit_plane(hit, ray, plane, t);
	return (hit);
}

double	ft_discriminant_cylinder(t_ray *ray, t_cylinder *cy, t_vctr oc)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = vec3_dot(ray->direction, ray->direction) - pow(vec3_dot(ray->direction,
				*cy->c_axis), 2);
	b = 2 * (vec3_dot(ray->direction, oc) - vec3_dot(ray->direction,
				*cy->c_axis) * vec3_dot(oc, *cy->c_axis));
	c = vec3_dot(oc, oc) - pow(vec3_dot(oc, *cy->c_axis), 2) - pow(cy->d / 2,
			2);
	discriminant = b * b - 4 * a * c;
	return (discriminant);
}

int	ft_assign_t_cy(t_ray *ray, double *t, t_vctr oc, t_cylinder *cy)
{
	double	t1;
	double	t2;
	double	sqrt_discriminant;
	double	a;
	double	b;

	a = vec3_dot(ray->direction, ray->direction) - pow(vec3_dot(ray->direction,
				*cy->c_axis), 2);
	b = 2 * (vec3_dot(ray->direction, oc) - vec3_dot(ray->direction,
				*cy->c_axis) * vec3_dot(oc, *cy->c_axis));
	sqrt_discriminant = sqrt(ft_discriminant_cylinder(ray, cy, oc));
	t1 = (-b - sqrt_discriminant) / (2 * a);
	t2 = (-b + sqrt_discriminant) / (2 * a);
	*t = -1;
	if (t1 > 1e-6)
	{
		*t = t1;
		return (0);
	}
	else if (t2 > 1e-6)
	{
		*t = t2;
		return (0);
	}
	return (1);
}

double	ft_distance_cylinder(t_hit *hit, t_cylinder *cy)
{
	t_vctr	projection;
	t_vctr	proj_point;
	t_vctr	vctr;
	double	distance;

	projection = vec3_scale(*cy->c_axis, vec3_dot(vec3_sub(hit->point,
					*cy->c_cntr), *cy->c_axis));
	proj_point = vec3_add(*cy->c_cntr, projection);
	vctr = vec3_sub(proj_point, *cy->c_cntr);
	distance = ft_magnitude(&vctr);
	if (distance <= cy->height)
		hit->normal = vec3_normalize(vec3_sub(hit->point, proj_point));
	return (distance);
}

t_hit	*intersect_cylinder(t_ray *ray, t_cylinder *cy)
{
	t_hit	*hit;
	double	discriminant;
	double	t;
	t_vctr	oc;

	hit = ft_hit();
	if (!hit)
		return (NULL);
	oc = vec3_sub(ray->origin, *cy->c_cntr);
	hit->hit = 0;
	hit->t = 0;
	discriminant = ft_discriminant_cylinder(ray, cy, oc);
	if (discriminant < 0)
		return (hit);
	if (ft_assign_t_cy(ray, &t, oc, cy))
		return (hit);
	hit->t = t;
	hit->hit = 1;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	if (ft_distance_cylinder(hit, cy) > cy->height)
		return (hit->hit = 0, hit);
	return (hit);
}

double	ft_discriminant_cone(t_vctr d, t_vctr co, t_cone *cone, t_vctr v)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	k;

	k = tan(cone->tang * M_PI / 180.0);
	a = vec3_dot(d, d) - (1.0 + k * k) * vec3_dot(d, v) * vec3_dot(d, v);
	b = 2.0 * (vec3_dot(co, d) - (1.0 + k * k) * vec3_dot(d, v) * vec3_dot(co,
				v));
	c = vec3_dot(co, co) - (1.0 + k * k) * vec3_dot(co, v) * vec3_dot(co, v);
	discriminant = b * b - 4.0 * a * c;
	return (discriminant);
}

int	ft_assign_t_cone(double discriminant, double *t, t_vctr d, t_cone *cone,
		t_vctr co, t_vctr v)
{
	double	t0;
	double	t1;
	double	a;
	double	b;
	double	k;

	k = tan(cone->tang * M_PI / 180.0);
	a = vec3_dot(d, d) - (1.0 + k * k) * vec3_dot(d, v) * vec3_dot(d, v);
	b = 2.0 * (vec3_dot(co, d) - (1.0 + k * k) * vec3_dot(d, v) * vec3_dot(co,
				v));
	t0 = (-b - sqrt(discriminant)) / (2.0 * a);
	t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t0 > 1e-6 && t1 > 1e-6)
		return (*t = fmin(t0, t1), 0);
	else if (t0 > 1e-6)
		return (*t = t0, 0);
	else if (t1 > 1e-6)
		return (*t = t1, 0);
	return (1);
}

double	ft_compute_discriminant(t_ray *ray, t_cone *cone, t_vctr *co, t_vctr *v)
{
	*co = vec3_sub(ray->origin, *(cone->vertex));
	*v = vec3_normalize(*(cone->axis));
	return ft_discriminant_cone(ray->direction, *co, cone, *v);
}

int	ft_validate_t_and_update(double discriminant, double *t, t_ray *ray, t_cone *cone, t_vctr co, t_vctr v)
{
	if (discriminant < 0)
		return (1);
	return ft_assign_t_cone(discriminant, t, ray->direction, cone, co, v);
}

int	ft_check_m_and_compute_normal(t_vctr intersection_point, t_cone *cone, t_vctr v, t_hit *hit)
{
	t_vctr	hit_to_vertex;
	double	m;
	t_vctr	normal;

	hit_to_vertex = vec3_sub(intersection_point, *(cone->vertex));
	m = vec3_dot(hit_to_vertex, v);
	if (m < cone->minm || m > cone->maxm)
		return (1);
	normal = vec3_sub(hit_to_vertex, vec3_scale(v, m));
	hit->normal = vec3_normalize(normal);
	return (0);
}

t_hit	*intersect_cone(t_ray *ray, t_cone *cone)
{
	t_hit	*hit;
	t_vctr	co;
	t_vctr	v;
	double	discriminant;
	double	t;
	t_vctr	intersection_point;

	if (!ray || !cone)
		return (NULL);
	hit = ft_hit();
	if (!hit)
		return (NULL);
	discriminant = ft_compute_discriminant(ray, cone, &co, &v);
	if (ft_validate_t_and_update(discriminant, &t, ray, cone, co, v))
		return (free(hit), NULL);
	intersection_point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	if (ft_check_m_and_compute_normal(intersection_point, cone, v, hit))
		return (free(hit), NULL);
	hit->t = t;
	hit->hit = 1;
	hit->point = intersection_point;
	return (hit);
}

