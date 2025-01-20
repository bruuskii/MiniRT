#include "../miniRT.h"

t_vctr	vec3_create(double x, double y, double z)
{
	t_vctr	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

double	*get_view_ports(t_cam *cam)
{
	double	viewport_height;
	double	aspect_ratio;
	double	viewport_width;
	double	*viewport;

	viewport = malloc(3 * sizeof(double));
	if (!viewport)
		return (NULL);
	aspect_ratio = (double)WIDTH / HEIGHT;
	viewport_height = 2.0 * tan(cam->fov * 0.5 * M_PI / 180.0);
	viewport_width = aspect_ratio * viewport_height;
	viewport[0] = viewport_height;
	viewport[1] = viewport_width;
	viewport[2] = aspect_ratio;
	return (viewport);
}

t_vctr	*ft_u_and_v(t_cam *cam)
{
	t_vctr	*u_v;
	t_vctr	u_vec;
	t_vctr	v_vec;

	u_v = malloc(2 * sizeof(t_vctr));
	if (!u_v)	
		return (NULL);
	u_vec = vec3_create(0, 1, 0);
	v_vec = vec3_cross(vec3_normalize(vec3_scale(*(cam->dir), -1)), u_vec);
	u_vec = vec3_cross(v_vec, vec3_normalize(vec3_scale(*(cam->dir), -1)));
	u_v[0] = u_vec;
	u_v[1] = v_vec;
	return (u_v);
}

t_vctr	*get_horiz_vert(t_cam *cam)
{
	t_vctr	horizontal;
	t_vctr	vertical;
	t_vctr	*h_v;
	t_vctr	*u_v;
	double	*viewport;

	h_v = malloc(2 * sizeof(t_vctr));
	if (!h_v)
		return (NULL);
	u_v = ft_u_and_v(cam);
	if (!u_v)
		return (NULL);
	viewport = get_view_ports(cam);
	if (!viewport)
		return (NULL);
	horizontal = vec3_scale(u_v[1], (viewport[2]) *  (viewport[0]));
	vertical = vec3_scale(u_v[0], viewport[0]);
	h_v[0] = horizontal;
	h_v[1] = vertical;
	free(viewport);
	free(u_v);
	return (h_v);
}

t_ray	*create_ray(t_cam *cam, double u, double v)
{
	t_ray	*ray;
	t_vctr	lower_left_corner;
	t_vctr	horizontal;
	t_vctr	vertical;
	t_vctr	*h_v;

	if (!cam)
		return (NULL);
	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	h_v = get_horiz_vert(cam);
	if (!h_v)
		return (NULL);
	horizontal = h_v[0];
	vertical = h_v[1];
	lower_left_corner = vec3_sub(*(cam->pos), vec3_add(vec3_scale(horizontal,
					0.5), vec3_add(vec3_scale(vertical, 0.5), vec3_normalize(vec3_scale(*(cam->dir), -1)))));
	ray->origin = *(cam->pos);
	ray->direction = vec3_normalize(vec3_sub(vec3_add(lower_left_corner,
					vec3_add(vec3_scale(horizontal, u), vec3_scale(vertical,
							v))), *(cam->pos)));
	free(h_v);
	return (ray);
}

t_ray	create_shadow_ray(t_hit hit, t_vctr point, t_light *light)
{
	t_vctr vec;
	t_ray s_ray;
	t_vctr normal;
	t_vctr light_dir;
	t_vctr biased;

	vec = vec3_sub(hit.point, point);
	normal = vec3_normalize(vec);
	biased = vec3_add(vec3_scale(normal, 1e-6), hit.point);
	light_dir = vec3_sub(*light->dir, biased);
	s_ray.origin = biased;
	s_ray.direction = vec3_normalize(light_dir);
	return (s_ray);
}