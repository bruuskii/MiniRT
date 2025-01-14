#include "../miniRT.h"

t_vctr	phong_lighting(t_vctr light_dir, t_vctr view_dir, t_vctr normal,
		t_material *material, t_light *light)
{
	t_vctr	reflect_dir;
	double	ambient;
	double	diffuse;
	double	specular;
	t_vctr	color;

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

// t_hit	*intersect_scene(t_ray *ray, t_scene *scene)
// {
// 	t_hit		*nearest_hit;
// 	double		nearest_t;
// 	t_sp		*sp;
// 	t_hit		*hit;
// 	t_plane		*pl;
// 	t_hit		*hit;
// 	t_cylinder	*cy;
// 	t_hit		*hit;

// 	nearest_hit = NULL;
// 	nearest_t = INFINITY;
// 	// t_scene *scene;
// 	sp = scene->sp;
// 	while (sp)
// 	{
// 		hit = intersect_sphere(ray, sp);
// 		if (hit && hit->t <= nearest_t)
// 		{
// 			if (nearest_hit)
// 				free(nearest_hit);
// 			nearest_hit = hit;
// 			nearest_t = hit->t;
// 		}
// 		else if (hit)
// 		{
// 			free(hit);
// 		}
// 		sp = sp->next;
// 	}
// 	pl = scene->pl;
// 	while (pl)
// 	{
// 		hit = intersect_plane(ray, pl);
// 		if (hit && hit->t < nearest_t)
// 		{
// 			if (nearest_hit)
// 				free(nearest_hit);
// 			nearest_hit = hit;
// 			nearest_t = hit->t;
// 		}
// 		else if (hit)
// 		{
// 			free(hit);
// 		}
// 		pl = pl->next;
// 	}
// 	cy = scene->cy;
// 	while (cy)
// 	{
// 		hit = intersect_cylinder(ray, cy);
// 		if (hit && hit->t < nearest_t)
// 		{
// 			if (nearest_hit)
// 				free(nearest_hit);
// 			nearest_hit = hit;
// 			nearest_t = hit->t;
// 		}
// 		else if (hit)
// 		{
// 			free(hit);
// 		}
// 		cy = cy->next;
// 	}
// 	return (nearest_hit);
// }

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
t_vctr	calculate_lighting(t_ray *ray, t_hit hit, t_vctr normal, t_scene *scene,
		t_material *material, t_light *light, double u, double v)
{
	t_vctr		color;
	t_ray		raysh;
	t_vctr		light_dir;
	t_vctr		view_dir;
	int			in_shadow;
	t_hit		*shadow_hit;
	t_sp		*current_sphere;
	t_plane		*current_plane;
	t_cone		*current_cone;
	t_cylinder	*current_cy;
	t_vctr		ambient;

	(void)u;
	(void)v;
	light_dir = vec3_normalize(vec3_sub(*light->dir, hit.point));
	view_dir = vec3_normalize(vec3_sub(ray->origin, hit.point));
	color = phong_lighting(light_dir, view_dir, normal, material, light);
	raysh.direction = light_dir;
	raysh.origin = vec3_add(hit.point, normal);
	in_shadow = 0;
	shadow_hit = NULL;
	current_sphere = scene->sp;
	while (current_sphere)
	{
		if (scene->sp && scene->sp->chess == 1)
		{
			t_hit *lol = intersect_sphere(&raysh, current_sphere);
			u = 0.5 + atan2(normal.z, normal.x) / (2 * M_PI);
			v = 0.5 - asin(normal.y) / M_PI;
			int square_u = floor(u * 16);
			int square_v = floor(v * 16);
			t_vctr pattern_color;
			t_vctr white = {255.0, 255.0, 255.0}; 
			t_vctr black = {0.0, 0.0, 0.0};
			pattern_color = (square_u + square_v) % 2 == 0 ? white : black; 

			if (lol->hit && !lol->t)
			{
				free(lol);
				t_vctr shadowed = vec3_scale(color, -1);
				return vec3_multiply(shadowed, pattern_color);
			}
			free(lol);
			t_vctr ambient = vec3_scale(*scene->alight->color, material->ambient);
			color = vec3_add(color, ambient);
			color = vec3_multiply(color, pattern_color);
		}
		shadow_hit = intersect_sphere(&raysh, current_sphere);
		if (shadow_hit && shadow_hit->hit && shadow_hit->t)
		{
			in_shadow = 1;
			free(shadow_hit);
			break ;
		}
		if (shadow_hit)
			free(shadow_hit);
		current_sphere = current_sphere->next;
	}
	current_plane = scene->pl;
	while (current_plane)
	{
		shadow_hit = intersect_plane(&raysh, current_plane);
		if (shadow_hit && shadow_hit->hit && shadow_hit->t)
		{
			in_shadow = 1;
			free(shadow_hit);
			break ;
		}
		if (shadow_hit)
			free(shadow_hit);
		current_plane = current_plane->next;
	}
	current_cone = scene->cn;
	while (current_cone)
	{
		shadow_hit = intersect_cone(&raysh, current_cone);
		if (shadow_hit && shadow_hit->hit && shadow_hit->t)
		{
			in_shadow = 1;
			free(shadow_hit);
			break ;
		}
		if (shadow_hit)
			free(shadow_hit);
		current_cone = current_cone->next;
	}
	current_cy = scene->cy;
	while (current_cy)
	{
		shadow_hit = intersect_cylinder(&raysh, current_cy);
		if (shadow_hit && shadow_hit->hit && shadow_hit->t)
		{
			in_shadow = 1;
			free(shadow_hit);
			break ;
		}
		if (shadow_hit)
			free(shadow_hit);
		current_cy = current_cy->next;
	}
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
