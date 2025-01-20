#include "../miniRT.h"

t_vctr	phong_lighting(t_vctr light_dir, t_vctr view_dir, t_vctr normal,
		t_material *material, t_light *light)
{
	double	ambient;
	double	diffuse;
	double	specular;
	t_vctr	color;
	t_vctr	reflect_dir;

	reflect_dir = vec3_sub(vec3_scale(normal, 2 * vec3_dot(normal, light_dir)),
			light_dir);
	ambient = material->ambient;
	diffuse = fmax(vec3_dot(normal, light_dir), 0.0) * material->diffuse;
	specular = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0),
			material->shininess) * material->specular;
	color = vec3_scale(material->color, ambient + diffuse);
	color = vec3_add(color, vec3_scale(*light->color, specular));
	color = vec3_scale(color, light->brightness);
	return (vec3_create(fmin(color.x, 255.0), fmin(color.y, 255.0),
			fmin(color.z, 255.0)));
}

double	vec3_length(t_vctr vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vctr	vec3_multiply(t_vctr v1, t_vctr v2)
{
	t_vctr	result;

	result.x = (v1.x * v2.x) / 255.0;
	result.y = (v1.y * v2.y) / 255.0;
	result.z = (v1.z * v2.z) / 255.0;
	return (result);
}

int	ft_sphere_param(t_scene *scene, t_ray raysh)
{
	t_sp		*current_sphere;
	t_hit		*shadow_hit;

	current_sphere = scene->sp;
	while (current_sphere)
	{
		shadow_hit = intersect_sphere(&raysh, current_sphere);
		if (shadow_hit && shadow_hit->hit && shadow_hit->t)
		{
			free(shadow_hit);
			return (1);
		}
		if (shadow_hit)
			free(shadow_hit);
		current_sphere = current_sphere->next;
	}
	return (0);
}
int	ft_hit_plane(t_scene *scene, t_ray raysh)
{
	t_plane		*current_plane;
	t_hit		*shadow_hit;

	current_plane = scene->pl;
	while (current_plane)
	{
		shadow_hit = intersect_plane(&raysh, current_plane);
		if (shadow_hit && shadow_hit->hit && shadow_hit->t)
		{
			free(shadow_hit);
			return (1);
		}
		if (shadow_hit)
			free(shadow_hit);
		current_plane = current_plane->next;
	}
	return (0);
}

int	ft_hit_cone(t_scene *scene, t_ray raysh)
{
	t_cone		*current_cone;
	t_hit		*shadow_hit;
	
	current_cone = scene->cn;
	while (current_cone)
	{
		shadow_hit = intersect_cone(&raysh, current_cone);
		if (shadow_hit && shadow_hit->hit && shadow_hit->t)
		{
			free(shadow_hit);
			return (1);
		}
		if (shadow_hit)
			free(shadow_hit);
		current_cone = current_cone->next;
	}
	return (0);
}

int	ft_hit_cy(t_scene *scene, t_ray raysh)
{
	t_cylinder	*current_cy;
	t_hit		*shadow_hit;

	current_cy = scene->cy;
	while (current_cy)
	{
		shadow_hit = intersect_cylinder(&raysh, current_cy);
		if (shadow_hit && shadow_hit->hit && shadow_hit->t)
		{
			free(shadow_hit);
			return (1);
		}
		if (shadow_hit)
			free(shadow_hit);
		current_cy = current_cy->next;
	}
	return (0);
}

t_vctr	calculate_lighting(t_ray *ray, t_hit hit, t_scene *scene, t_material *material, t_light *light)
{
	t_vctr		color;
	t_ray		raysh;
	t_vctr		light_dir;
	t_vctr		view_dir;
	int			in_shadow;
	t_vctr		ambient;

	light_dir = vec3_normalize(vec3_sub(*light->dir, hit.point));
	view_dir = vec3_normalize(vec3_sub(ray->origin, hit.point));
	color = phong_lighting(light_dir, view_dir, hit.normal, material, light);
	raysh.direction = light_dir;
	raysh.origin = vec3_add(hit.point, hit.normal);
	in_shadow = 0;
	if (ft_sphere_param(scene, raysh))
		in_shadow = 1;
	if (ft_hit_plane(scene, raysh))
		in_shadow = 1;
	if (ft_hit_cy(scene, raysh))
		in_shadow = 1;
	if (ft_hit_cone(scene, raysh))	
		in_shadow = 1;
	if (in_shadow)
	{
		ambient = vec3_scale((t_vctr){10, 10, 10}, material->ambient);
		color = vec3_scale(vec3_add(ambient, color), 0.5);
	}
	else
	{
		color.x = fmin(fmax(color.x, 0.0), 255.0);
		color.y = fmin(fmax(color.y, 0.0), 255.0);
		color.z = fmin(fmax(color.z, 0.0), 255.0);
	}
	return (color);
}
