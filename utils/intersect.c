#include "../miniRT.h"

double	ft_magnitude(t_vctr *vec)
{
	return (sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z)));
}

t_hit	*ft_hit()
{
	t_hit	*hit_point;

	hit_point = malloc(sizeof(t_hit));
	if (!hit_point)
		return (printf("hit point non-allocated"), NULL);
	hit_point->hit = 0;
	hit_point->t = 0;
	return (hit_point);
}
t_hit	*intersect_sphere(t_ray *ray, t_sp *sphere)
{
	t_hit	*hit;
	t_vctr	oc;
	double	a;
	double	r;
	double	b;
	double	c;
	double	discriminant;
	double	sqrt_discriminant;
	double	t1;
	double	t2;
	t_vctr	original_normal;
	double	bump_intensity;
	double	noise_x;
	double	noise_y;
	double	noise_z;
	t_vctr	noise_offset;

	hit = ft_hit();
	oc = vec3_sub(ray->origin, *sphere->cntr);
	a = vec3_dot(ray->direction, ray->direction);
	r = sphere->d / 2;
	b = 2.0 * vec3_dot(oc, ray->direction);
	c = vec3_dot(oc, oc) - r * r;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		hit->hit = 0;
		return (hit);
	}
	sqrt_discriminant = sqrt(discriminant);
	t1 = (-b - sqrt_discriminant) / (2.0 * a);
	t2 = (-b + sqrt_discriminant) / (2.0 * a);
	if (t1 > 1e-6)
	{
		hit->t = t1;
		hit->hit = 1;
	}
	else if (t2 > 1e-6)
	{
		hit->t = t2;
		hit->hit = 1;
	}
	else
		return (hit);
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	original_normal = vec3_normalize(vec3_sub(hit->point, *sphere->cntr));

	if (sphere->fl == 1)
	{
		bump_intensity = 0.1;
		noise_x = fmod(sin(hit->point.x * 10), 1.0);
		noise_y = fmod(cos(hit->point.y * 10), 1.0);
		noise_z = fmod(tan(hit->point.z * 10), 1.0);
		noise_offset = (t_vctr){noise_x * bump_intensity, noise_y * bump_intensity,
			noise_z * bump_intensity};
		hit->normal = vec3_normalize(vec3_add(original_normal, noise_offset));
	}
	else
		hit->normal = original_normal;
	return (hit);

}

t_hit	*intersect_plane(t_ray *ray, t_plane *plane)
{
	t_hit			*hit;
	t_vctr			denom;
	t_vctr			nom;
	double			den;
	t_vctr			ray_to_plane;
	double			t;
	t_vctr			intersection;
	t_vctr			up;
	t_vctr			local_point;
	double			u;
	double			v;
	const double 	m_w = 200;
	const double 	m_h = 200;
	const double	m_h_00 = 50;

	hit = ft_hit();
	if (!hit)
		return (NULL);
	hit->hit = 0;
	hit->t = 0;
	denom = vec3_normalize(ray->direction);
	nom = *plane->normal;
	den= vec3_dot(denom, nom);
	if (fabs(den) < 1e-6)
		return (hit);
	ray_to_plane = vec3_sub(*plane->point, ray->origin);
	t = vec3_dot(ray_to_plane, nom) / den;
	if (t < 1e-6)
		return (hit);
	intersection = vec3_add(ray->origin, vec3_scale(denom, t));
	t_vctr plane_u, plane_v;
	if (!plane->normal->z)
	{
		if (fabs(nom.z) > 0.9)
		{
			plane_u = (t_vctr){1, 0, 0};
			plane_v = (t_vctr){0, 1, 0};
		}
		else
		{
			if (fabs(nom.y) < 0.9)
				up = (t_vctr){0, 1, 0};
			else
				up = (t_vctr){0, 0, 1};
			plane_u = vec3_normalize(vec3_cross(nom, up));
			plane_v = vec3_normalize(vec3_cross(nom, plane_u));
		}
		local_point = vec3_sub(intersection, *plane->point);
		u = vec3_dot(local_point, plane_u);
		v = vec3_dot(local_point, plane_v);
		if (fabs(u) > m_w || (fabs(v) >= m_h
				|| fabs(v) <= m_h_00))
			return (hit);
	}
	hit->hit = 1;
	hit->t = t;
	hit->point = intersection;
	if (den < 0)
		hit->normal = nom;
	else
		hit->normal = vec3_scale(nom, -1);
	return (hit);
}

t_hit	*intersect_cylinder(t_ray *ray, t_cylinder *cy)
{
	t_hit	*hit;
	t_vctr	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrt_discriminant;
	double	t1;
	double	t2;
	double	t;
	t_vctr	projection;
	t_vctr	proj_point;
	t_vctr	vctr;
	double	distance;

	hit = ft_hit();
	if (!hit)
		return (NULL);
	hit->hit = 0;
	hit->t = 0;
	oc = vec3_sub(ray->origin, *cy->c_cntr);
	a = vec3_dot(ray->direction, ray->direction) - pow(vec3_dot(ray->direction,
				*cy->c_axis), 2);
	b = 2 * (vec3_dot(ray->direction, oc) - vec3_dot(ray->direction,
				*cy->c_axis) * vec3_dot(oc, *cy->c_axis));
	c = vec3_dot(oc, oc) - pow(vec3_dot(oc, *cy->c_axis), 2) - pow(cy->d / 2,
			2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit);
	sqrt_discriminant = sqrt(discriminant);
	t1 = (-b - sqrt_discriminant) / (2 * a);
	t2 = (-b + sqrt_discriminant) / (2 * a);
	t = -1;
	if (t1 > 1e-6)
		t = t1;
	else if (t2 > 1e-6)
		t = t2;
	else
		return (hit);
	hit->t = t;
	hit->hit = 1;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	projection = vec3_scale(*cy->c_axis, vec3_dot(vec3_sub(hit->point,
					*cy->c_cntr), *cy->c_axis));
	proj_point = vec3_add(*cy->c_cntr, projection);
	vctr = vec3_sub(proj_point, *cy->c_cntr);
	distance = ft_magnitude(&vctr);
	if (distance > cy->height)
	{
		hit->hit = 0;
		return (hit);
	}
	hit->normal = vec3_normalize(vec3_sub(hit->point, proj_point));
	return (hit);
}

t_hit	*intersect_cone(t_ray *ray, t_cone *cone)
{
	t_hit	*hit;
	t_vctr	co;
	t_vctr	d;
	t_vctr	v;
	double	k;
	double	d_dot_v;
	double	co_dot_v;
	double	d_dot_d;
	double	co_dot_d;
	double	co_dot_co;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrt_discriminant;
	double	t0;
	double	t1;
	double	t;
	t_vctr	intersection_point;
	t_vctr	hit_to_vertex;
	double	m;
	t_vctr	normal;

	if (!ray || !cone)
		return (NULL);
	hit = malloc(sizeof(t_hit));
	if (!hit)
		return (NULL);
	co = vec3_sub(ray->origin, *(cone->vertex));
	d = ray->direction;
	v = vec3_normalize(*(cone->axis));
	k = tan(cone->tang * M_PI / 180.0);
	d_dot_v = vec3_dot(d, v);
	co_dot_v = vec3_dot(co, v);
	d_dot_d = vec3_dot(d, d);
	co_dot_d = vec3_dot(co, d);
	co_dot_co = vec3_dot(co, co);
	a = d_dot_d - (1.0 + k * k) * d_dot_v * d_dot_v;
	b = 2.0 * (co_dot_d - (1.0 + k * k) * d_dot_v * co_dot_v);
	c = co_dot_co - (1.0 + k * k) * co_dot_v * co_dot_v;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0 || fabs(a) < 1e-6)
	{
		free(hit);
		return (NULL);
	}
	sqrt_discriminant = sqrt(discriminant);
	t0 = (-b - sqrt_discriminant) / (2.0 * a);
	t1 = (-b + sqrt_discriminant) / (2.0 * a);
	if (t0 > 1e-6 && t1 > 1e-6)
		t = fmin(t0, t1);
	else if (t0 > 1e-6)
		t = t0;
	else if (t1 > 1e-6)
		t = t1;
	else
	{
		free(hit);
		return (NULL);
	}
	intersection_point = vec3_add(ray->origin, vec3_scale(d, t));
	hit_to_vertex = vec3_sub(intersection_point, *(cone->vertex));
	m = vec3_dot(hit_to_vertex, v);
	if (m < cone->minm || m > cone->maxm)
	{
		free(hit);
		return (NULL);
	}
	normal = vec3_sub(hit_to_vertex, vec3_scale(v, m));
	normal = vec3_normalize(normal);
	hit->t = t;
	hit->hit = 1;
	hit->point = intersection_point;
	hit->normal = normal;
	return (hit);
}
