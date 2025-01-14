#include "miniRT.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_free_all(t_scene **scene)
{
	t_light		*lt;
	t_light		*lt_next;

	if (!scene || !*scene)
		return ;
	if ((*scene)->cam)
	{
		free((*scene)->cam->dir);
		free((*scene)->cam->pos);
		free((*scene)->cam);
	}
	lt = (*scene)->light;
	while (lt)
	{
		lt_next = lt->next;
		free(lt->color);
		free(lt->dir);
		free(lt);
		lt = lt_next;
	}
	if ((*scene)->alight)
	{
		free((*scene)->alight->color);
		free((*scene)->alight);
	}
}

void	put_pixel_to_image(char *img_data, int x, int y, int color)
{
	int	offset;

	offset = ((HEIGHT - 1 - y) * WIDTH + x) * 4;
	*(unsigned int *)(img_data + offset) = color;
}

double	dgrs_to_rdn(double angle)
{
	return (angle * (M_PI / 180.0));
}

void	convert_3d_to_2d(double x, double y, double z, double d, int *x2,
		int *y2, double fov)
{
	double	aspect_ratio;
	double	scale;
	double	proj_x;
	double	proj_y;

	aspect_ratio = (double)WIDTH / HEIGHT;
	scale = tan(fov / 2.0) * 2.0;
	if (z <= 0)
	{
		*x2 = *y2 = -1;
		return ;
	}
	proj_x = (x / z) * d * scale * aspect_ratio;
	proj_y = (y / z) * d * scale;
	*x2 = (int)(proj_x + (WIDTH / 2));
	*y2 = (int)(proj_y + (HEIGHT / 2));
}

double	calculate_distance(double fov)
{
	double	d;
	double	fv;

	fv = dgrs_to_rdn(fov);
	d = WIDTH / (2 * tan(fv / 2.0));
	return (d);
}

t_vctr	amb_color(t_vctr ambiant, t_material *mtrl)
{
	t_vctr	amb;
	t_vctr	color;
	double	ambient;

	color = mtrl->color;
	ambient = mtrl->ambient;
	amb.x = ambiant.x * color.x * ambient / 255;
	amb.y = ambiant.y * color.y * ambient / 255;
	amb.z = ambiant.z * color.z * ambient / 255;
	return (amb);
}

void	render_scene(void *img, t_scene *scene)
{
	t_ray	*ray;
	t_sp	*sp;
	t_hit	*hit;
	char	*img_data;
	double	u;
	double	v;
	t_vctr	final_color;
	t_light	*light;
	t_vctr	light_color;

	int x, y;
	int bits_per_pixel, size_line, endian;
	img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	sp = (t_sp *)scene->sp;
	hit = NULL;
	y = 0;
	if (!scene)
		return ;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			u = ((double)x / (WIDTH - 1));
			v = ((double)y / (HEIGHT - 1));
			ray = create_ray(scene->cam, u, v);
			hit = intersect_sphere(ray, scene->sp);
			//hit->type = SPHERE;
			if (!ray)
				return ;
			if (hit && hit->hit)
			{
				final_color = (t_vctr){0, 0, 0};
				light = scene->light;
				while (light)
				{
					light_color = calculate_lighting(ray, *hit, hit->normal,
							scene, sp->mtrl, light, u, v);
					final_color.x += light_color.x;
					final_color.y += light_color.y;
					final_color.z += light_color.z;
					if (light)
						light = light->next;
				}
				final_color.x = fmin(fmax(final_color.x, 0), 255);
				final_color.y = fmin(fmax(final_color.y, 0), 255);
				final_color.z = fmin(fmax(final_color.z, 0), 255);
				put_pixel_to_image(img_data, x, y, create_trgb(0,
						(int)final_color.x, (int)final_color.y,
						(int)final_color.z));
			}
			free(hit);
			free(ray);
			x++;
		}
		y++;
	}
}

void	render_scene_cn(void *img, t_scene *scene)
{
	t_ray	*ray;
	t_cone	*sp;
	t_hit	*hit;
	char	*img_data;
	double	u;
	double	v;
	t_vctr	final_color;
	t_light	*light;
	t_vctr	light_color;

	int x, y;
	int bits_per_pixel, size_line, endian;
	img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	sp = (t_cone *)scene->cn;
	y = 0;
	hit  = NULL;
	if (!scene)
		return ;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			u = ((double)x / (WIDTH - 1));
			v = ((double)y / (HEIGHT - 1));
			ray = create_ray(scene->cam, u, v);
			hit = intersect_cone(ray, scene->cn);
			if (hit && hit->hit)
			{
				final_color = (t_vctr){0, 0, 0};
				light = scene->light;
				while (light)
				{
					light_color = calculate_lighting(ray, *hit, hit->normal,
							scene, sp->mtrl, light, u, v);
					final_color.x += light_color.x;
					final_color.y += light_color.y;
					final_color.z += light_color.z;
					if (light)
						light = light->next;
				}
				final_color.x = fmin(fmax(final_color.x, 0), 255);
				final_color.y = fmin(fmax(final_color.y, 0), 255);
				final_color.z = fmin(fmax(final_color.z, 0), 255);
				put_pixel_to_image(img_data, x, y, create_trgb(0,
						(int)final_color.x, (int)final_color.y,
						(int)final_color.z));
			}
			free(hit);
			free(ray);
			x++;
		}
		y++;
	}
}

void	render_scene_plane(void *img, t_scene *scene)
{
	t_ray	*ray;
	t_hit	*hit;
	char	*img_data;
	double	u;
	double	v;
	t_vctr	final_color;
	t_light	*light;
	t_vctr	light_color;

	int x, y;
	int bits_per_pixel, size_line, endian;
	img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	y = 0;
	hit = NULL;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			u = ((double)x / (WIDTH - 1));
			v = ((double)y / (HEIGHT - 1));
			ray = create_ray(scene->cam, u, v);
			if (!ray)
				return ;
			hit = intersect_plane(ray, scene->pl);
			if (!hit)
			{
				free(ray);
				continue ;
			}
			if (hit && hit->hit)
			{
				//hit->type = PLANE;
				final_color = (t_vctr){0, 0, 0};
				light = scene->light;
				while (light)
				{
					light_color = calculate_lighting(ray, *hit, hit->normal,
							scene, scene->pl->mtrl, light, u, v);
					final_color.x += light_color.x;
					final_color.y += light_color.y;
					final_color.z += light_color.z;
					light = light->next;
				}
				final_color.x = fmin(fmax(final_color.x, 0), 255);
				final_color.y = fmin(fmax(final_color.y, 0), 255);
				final_color.z = fmin(fmax(final_color.z, 0), 255);
				put_pixel_to_image(img_data, x, y, create_trgb(0,
						(int)final_color.x, (int)final_color.y,
						(int)final_color.z));
			}
			free(hit);
			free(ray);
			x++;
		}
		y++;
	}
}

void	render_scene_cy(void *img, t_scene *scene)
{
	t_ray	*ray;
	t_hit	*hit;
	char	*img_data;
	double	u;
	double	v;
	t_vctr	final_color;
	t_light	*light;
	t_vctr	light_color;

	int x, y;
	int bits_per_pixel, size_line, endian;
	img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	y = 0;
	hit = NULL;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			u = ((double)x / (WIDTH - 1));
			v = ((double)y / (HEIGHT - 1));
			ray = create_ray(scene->cam, u, v);
			if (ray == 0)
				return ;
			hit = intersect_cylinder(ray, scene->cy);
			// hit->type = CYLINDRE;
			if (hit && hit->hit)
			{
				final_color = (t_vctr){0, 0, 0};
				light = scene->light;
				while (light)
				{
					light_color = calculate_lighting(ray, *hit, hit->normal,
							scene, scene->cy->mtrl, light, u, v);
					final_color.x += light_color.x;
					final_color.y += light_color.y;
					final_color.z += light_color.z;
					light = light->next;
				}
				final_color.x = fmin(fmax(final_color.x, 0), 255);
				final_color.y = fmin(fmax(final_color.y, 0), 255);
				final_color.z = fmin(fmax(final_color.z, 0), 255);
				put_pixel_to_image(img_data, x, y, create_trgb(0,
						(int)final_color.x, (int)final_color.y,
						(int)final_color.z));
			}
			free(ray);
			free(hit);
			x++;
		}
		y++;
	}
}

t_material	*ft_material(t_scene *scene, double dif, double spec, double sh)
{
	t_material	*mtrl;

	mtrl = malloc(sizeof(t_material));
	if (!mtrl)
	{
		printf("Failed to allocate cone material\n");
		return (NULL);
	}
	mtrl->ambient = scene->alight->ratio;
	mtrl->diffuse = dif;
	mtrl->specular = spec;
	mtrl->shininess = sh;
	return (mtrl);
}

void	ft_scene_cone(t_scene *scene, t_win *data)
{
	t_cone		*con;
	t_cone		*next_cone;

	while (scene->cn)
	{
		con = (t_cone *)(scene->cn);
		next_cone = con->next;
		con->mtrl = ft_material(scene, 0.5, 0.5,60);
		if (!con->mtrl)
		{
			printf("Failed to allocate sphere material\n");
			free(con);
			free(scene);
			return ;
		}
		con->mtrl->color = *con->color;
		render_scene_cn(data->img, scene);
		free(con->mtrl);
		free(con->axis);
		free(con->color);
		free(con->vertex);
		free(con);
		scene->cn = next_cone;
	}
}

void	ft_scene_cylinder(t_scene *scene, t_win *data)
{
	t_cylinder	*cyl;
	t_cylinder  *cy_next;

	while (scene->cy)
	{
		cyl = (t_cylinder *)(scene->cy);
		cy_next = cyl->next;
		cyl->mtrl = ft_material(scene, 0.5, 0.5,60);
		if (!cyl->mtrl)
		{
			printf("Failed to allocate cylinder material\n");
			free(cyl);
			free(scene);
			return ;
		}
		cyl->mtrl->color = *cyl->color;
		render_scene_cy(data->img, scene);
		free(cyl->c_axis);
		free(cyl->c_cntr);
		free(cyl->color);
		if (cyl->mtrl)
			free(cyl->mtrl);
		free(cyl);
		scene->cy = cy_next;
	}
}

void	ft_scene_plane(t_scene *scene, t_win *data)
{
	t_plane		*plane;
	t_plane		*pl_next;

	while (scene->pl)
	{
		plane = (t_plane *)(scene->pl);
		pl_next = plane->next;
		plane->mtrl = ft_material(scene, 0.6, 0.6, 60);
		if (!plane->mtrl)
		{
			printf("Failed to allocate plane material\n");
			free(plane);
			free(scene);
			return ;
		}
		plane->mtrl->color = *plane->color;
		render_scene_plane(data->img, scene);
		free(plane->point);
		free(plane->normal);
		free(plane->color);
		if (plane->mtrl)
			free(plane->mtrl);
		free(plane);
		scene->pl = pl_next;
	}
}

void	ft_scene_sphere(t_scene *scene, t_win *data)
{
	t_sp		*sphere;
	t_sp		*sp_next;

	while (scene->sp)
	{
		sphere = scene->sp;
		sp_next = sphere->next;
		sphere->mtrl = ft_material(scene, 0.5, 0.5, 60);
		if (!sphere->mtrl)
		{
			printf("Failed to allocate sphere material\n");
			free(sphere);
			free(scene);
			return ;
		}
		sphere->mtrl->color = *sphere->color;
		render_scene(data->img, scene);
		free(sphere->cntr);
		free(sphere->color);
		if (sphere->mtrl)
			free(sphere->mtrl);
		free(sphere);
		scene->sp = sp_next;
	}
}

void	ft_display_scene(t_scene *scene, t_win *data)
{
	if (scene->pl)
		ft_scene_plane(scene, data);
	if (scene->sp)
		ft_scene_sphere(scene, data);
	if (scene->cy)
		ft_scene_cylinder(scene, data);
	if (scene->cn)
		ft_scene_cone(scene, data);
	ft_free_all(&scene);
	free(scene);
	mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, ft_escape_key, data);
	mlx_hook(data->win, 17, 0, ft_close, data);
	mlx_loop(data->ptr);
}