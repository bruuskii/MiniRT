#include "../miniRT.h"

t_view	*ft_view(t_vctr light_dir, t_vctr view_dir, t_light *light)
{
	t_view	*ptr;

	ptr = malloc(sizeof(t_view));
	if (!ptr)
		return (NULL);
	ptr->light_dir = light_dir;
	ptr->view_dir = view_dir;
	ptr->light = light;
	return (ptr);
}

t_vctr	phong_lighting(t_view *view, t_vctr normal, t_material *material)
{
	double	ambient;
	double	diffuse;
	double	specular;
	t_vctr	color;
	t_vctr	reflect_dir;

	reflect_dir = vec3_sub(vec3_scale(normal, 2 * vec3_dot(normal,
					view->light_dir)), view->light_dir);
	ambient = material->ambient;
	diffuse = fmax(vec3_dot(normal, view->light_dir), 0.0) * material->diffuse;
	specular = pow(fmax(vec3_dot(view->view_dir, reflect_dir), 0.0),
			material->shininess) * material->specular;
	color = vec3_scale(material->color, ambient + diffuse);
	color = vec3_add(color, vec3_scale(*view->light->color, specular));
	color = vec3_scale(color, view->light->brightness);
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
	t_sp	*current_sphere;
	t_hit	*shadow_hit;

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
	t_plane	*current_plane;
	t_hit	*shadow_hit;

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
	t_cone	*current_cone;
	t_hit	*shadow_hit;

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

t_vctr	light_colors(t_light *light, t_hit hit, t_material *material,
		t_ray *ray)
{
	t_vctr	color;
	t_vctr	light_dir;
	t_vctr	view_dir;
	t_view	*view;

	light_dir = vec3_normalize(vec3_sub(*light->dir, hit.point));
	view_dir = vec3_normalize(vec3_sub(ray->origin, hit.point));
	view = ft_view(light_dir, view_dir, light);
	color = phong_lighting(view, hit.normal, material);
	free(view);
	return (color);
}

int	is_in_shaddow(t_scene *scene, t_ray raysh)
{
	int	in_shadow;

	in_shadow = 0;
	if (ft_sphere_param(scene, raysh))
		in_shadow = 1;
	if (ft_hit_plane(scene, raysh))
		in_shadow = 1;
	if (ft_hit_cy(scene, raysh))
		in_shadow = 1;
	if (ft_hit_cone(scene, raysh))
		in_shadow = 1;
	return (in_shadow);
}

t_vctr	calculate_lighting(t_ray *ray, t_hit hit, t_scene *scene,
		t_material *material, t_light *light)
{
	t_vctr	color;
	t_ray	raysh;
	int		in_shadow;
	t_vctr	ambient;
	t_vctr	light_dir;

	light_dir = vec3_normalize(vec3_sub(*light->dir, hit.point));
	raysh.direction = light_dir;
	raysh.origin = vec3_add(hit.point, hit.normal);
	color = light_colors(light, hit, material, ray);
	in_shadow = is_in_shaddow(scene, raysh);
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
