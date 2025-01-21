#include "miniRT.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_free_all(t_scene **scene)
{
	t_light	*lt;
	t_light	*lt_next;

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

t_ray	*get_ray(t_scene *scene, int x, int y)
{
	double	u;
	double	v;
	t_ray	*ray;

	u = ((double)x / (WIDTH - 1));
	v = ((double)y / (HEIGHT - 1));
	ray = create_ray(scene->cam, u, v);
	if (!ray)
		return (NULL);
	return (ray);
}

t_vctr	ft_final_color(t_ray *ray, t_hit *hit, t_scene *scene, t_material *mtrl)
{
	t_vctr	final_color;
	t_light	*light;
	t_vctr	light_color;
	t_view	*view;

	final_color = (t_vctr){0, 0, 0};
	light = scene->light;
	while (light)
	{
		view = ft_view(final_color, final_color, light, ray);
		if (!view)
			continue ;
		light_color = calculate_lighting(view, *hit, scene, mtrl);
		final_color.x += light_color.x;
		final_color.y += light_color.y;
		final_color.z += light_color.z;
		free(view);
		if (light)
			light = light->next;
	}
	final_color.x = fmin(fmax(final_color.x, 0), 255);
	final_color.y = fmin(fmax(final_color.y, 0), 255);
	final_color.z = fmin(fmax(final_color.z, 0), 255);
	return (final_color);
}

void	ft_render(t_scene *scene, char *img_data, int y, t_material *mtrl)
{
	int		x;
	t_ray	*ray;
	t_hit	*hit;
	t_vctr	final_color;

	x = 0;
	while (x < WIDTH)
	{
		ray = get_ray(scene, x, y);
		hit = intersect_sphere(ray, scene->sp);
		if (!ray)
			return ;
		if (hit && hit->hit)
		{
			final_color = ft_final_color(ray, hit, scene, mtrl);
			put_pixel_to_image(img_data, x, y, create_trgb(0,
					(int)final_color.x, (int)final_color.y,
					(int)final_color.z));
		}
		free(hit);
		free(ray);
		x++;
	}
}

void	render_scene(void *img, t_scene *scene)
{
	char	*img_data;
	int		y;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	y = 0;
	if (!scene)
		return ;
	while (y < HEIGHT)
	{
		ft_render(scene, img_data, y, scene->sp->mtrl);
		y++;
	}
}

void	render_scene_cn_rows(t_scene *scene, char *img_data, int y,
		t_material *mtrl)
{
	int		x;
	t_ray	*ray;
	t_hit	*hit;
	t_vctr	final_color;

	x = 0;
	while (x < WIDTH)
	{
		ray = get_ray(scene, x, y);
		hit = intersect_cone(ray, scene->cn);
		if (!ray)
			return ;
		if (hit && hit->hit)
		{
			final_color = ft_final_color(ray, hit, scene, mtrl);
			put_pixel_to_image(img_data, x, y, create_trgb(0,
					(int)final_color.x, (int)final_color.y,
					(int)final_color.z));
		}
		free(hit);
		free(ray);
		x++;
	}
}

void	render_scene_cn(void *img, t_scene *scene)
{
	char	*img_data;
	int		y;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	y = 0;
	if (!scene)
		return ;
	while (y < HEIGHT)
	{
		render_scene_cn_rows(scene, img_data, y, scene->cn->mtrl);
		y++;
	}
}

void	render_scene_plane_rows(t_scene *scene, char *img_data, int y,
		t_material *mtrl)
{
	int		x;
	t_ray	*ray;
	t_hit	*hit;
	t_vctr	final_color;

	x = 0;
	while (x < WIDTH)
	{
		ray = get_ray(scene, x, y);
		hit = intersect_plane(ray, scene->pl);
		if (!ray)
			return ;
		if (hit && hit->hit)
		{
			final_color = ft_final_color(ray, hit, scene, mtrl);
			put_pixel_to_image(img_data, x, y, create_trgb(0,
					(int)final_color.x, (int)final_color.y,
					(int)final_color.z));
		}
		free(hit);
		free(ray);
		x++;
	}
}

void	render_scene_plane(void *img, t_scene *scene)
{
	char	*img_data;
	int		y;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	y = 0;
	while (y < HEIGHT)
	{
		render_scene_plane_rows(scene, img_data, y, scene->pl->mtrl);
		y++;
	}
}

void	render_scene_cy_rows(t_scene *scene, char *img_data, int y,
		t_material *mtrl)
{
	int		x;
	t_ray	*ray;
	t_hit	*hit;
	t_vctr	final_color;

	x = 0;
	while (x < WIDTH)
	{
		ray = get_ray(scene, x, y);
		hit = intersect_cylinder(ray, scene->cy);
		if (!ray)
			return ;
		if (hit && hit->hit)
		{
			final_color = ft_final_color(ray, hit, scene, mtrl);
			put_pixel_to_image(img_data, x, y, create_trgb(0,
					(int)final_color.x, (int)final_color.y,
					(int)final_color.z));
		}
		free(hit);
		free(ray);
		x++;
	}
}

void	render_scene_cy(void *img, t_scene *scene)
{
	char	*img_data;
	int		y;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	y = 0;
	while (y < HEIGHT)
	{
		render_scene_cy_rows(scene, img_data, y, scene->cy->mtrl);
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
	t_cone	*con;
	t_cone	*next_cone;

	while (scene->cn)
	{
		con = (t_cone *)(scene->cn);
		next_cone = con->next;
		con->mtrl = ft_material(scene, 0.5, 0.5, 60);
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
	t_cylinder	*cy_next;

	while (scene->cy)
	{
		cyl = (t_cylinder *)(scene->cy);
		cy_next = cyl->next;
		cyl->mtrl = ft_material(scene, 0.5, 0.5, 60);
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
	t_plane	*plane;
	t_plane	*pl_next;

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
	t_sp	*sphere;
	t_sp	*sp_next;

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
