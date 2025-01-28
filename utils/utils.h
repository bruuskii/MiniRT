/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:54:49 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/27 22:49:20 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../structs.h"

void		ft_free_objects(t_scene *scene);
int			is_zero_vector(t_vctr v);
void		ft_initialize_cone_data(t_ray *ray, t_cone *cone,
				t_cone_data *data);
void		ft_calculate_quadratic_coeffs(t_vctr d, t_cone_data *data);
t_hit		*ft_hit(void);
double		ft_calculate_discriminant_sphere(t_ray *ray, t_sp *sphere);
int			ft_assign_t(t_hit *hit, t_ray *ray, double discriminant,
				t_sp *sphere);
t_hit		*intersect_sphere(t_ray *ray, t_sp *sphere);
void		ft_get_plane_axes(t_vctr *plane_u, t_vctr *plane_v, t_vctr *normal);
int			ft_resize_plane_00(t_vctr intersection, t_plane *plane);
t_vctr		ft_calculate_intersection_plane(t_vctr denom, t_plane *plane,
				double t, t_ray *ray);
void		ft_assign_hit_plane(t_hit *hit, t_ray *ray, t_plane *plane,
				double t);
t_hit		*intersect_plane(t_ray *ray, t_plane *plane);
double		ft_discriminant_cylinder(t_ray *ray, t_cylinder *cy, t_vctr oc);
int			ft_assign_t_cy(t_ray *ray, double *t, t_vctr oc, t_cylinder *cy);
double		ft_distance_cylinder(t_hit *hit, t_cylinder *cy);
t_hit		*intersect_cylinder(t_ray *ray, t_cylinder *cy);
double		ft_calculate_k(double tang);
double		ft_calculate_discriminant(t_cone_data *data);
int			ft_solve_quadratic(double a, double b, double discriminant,
				double *t);
int			ft_validate_and_solve(t_cone_data *data, double *t);
int			ft_check_intersection_constraints(t_vctr intersection, t_cone *cone,
				t_vctr v, t_hit *hit);
t_hit		*intersect_cone(t_ray *ray, t_cone *cone);
t_view		*ft_view(t_vctr light_dir, t_vctr view_dir, t_light *light,
				t_ray *ray);
t_vctr		phong_lighting(t_view *view, t_vctr normal, t_material *material);
double		vec3_length(t_vctr vec);
t_vctr		vec3_multiply(t_vctr v1, t_vctr v2);
t_vctr		light_colors(t_light *light, t_hit hit, t_material *material,
				t_ray *ray);
int			ft_sphere_param(t_scene *scene, t_ray raysh);
int			ft_hit_plane(t_scene *scene, t_ray raysh);
int			ft_hit_cone(t_scene *scene, t_ray raysh);
int			ft_hit_cy(t_scene *scene, t_ray raysh);
int			is_in_shaddow(t_scene *scene, t_ray raysh);
t_vctr		calculate_lighting(t_view *view, t_hit hit, t_scene *scene,
				t_material *material);
t_sp		*ft_new(t_sp *content);
t_cone		*ft_new_cone(t_cone *content);
t_plane		*ft_new_pl(t_plane *content);
t_cylinder	*ft_new_cy(t_cylinder *content);
void		ft_add_back(t_sp **objs, t_sp *node);
void		ft_add_back_pl(t_plane **objs, t_plane *node);
void		ft_add_back_cy(t_cylinder **objs, t_cylinder *node);
t_light		*ft_new_lt(void);
t_alight	*ft_a_light(void);
void		ft_add_back_lt(t_light **objs, t_light *node);
void		ft_add_back_cn(t_cone **cn, t_cone *node);
double		*get_view_ports(t_cam *cam);
t_vctr		*ft_u_and_v(t_cam *cam);
t_vctr		*get_horiz_vert(t_cam *cam);
t_ray		*create_ray(t_cam *cam, double u, double v);
t_ray		create_shadow_ray(t_hit hit, t_vctr point, t_light *light);
t_vctr		vec3_add(t_vctr v1, t_vctr v2);
t_vctr		vec3_sub(t_vctr v1, t_vctr v2);
t_vctr		vec3_scale(t_vctr v, double t);
void		ft_print_and_exit(char *s, int stat);
t_vctr		vec3_cross(t_vctr v1, t_vctr v2);
double		vec3_dot(t_vctr v1, t_vctr v2);
t_vctr		vec3_normalize(t_vctr v);
t_vctr		vec3_create(double x, double y, double z);
t_world		*new_node(void *ptr, t_type type);
void		ft_add_back_world(t_world **head, t_world *node);
int			get_farther_object(t_sp *sp, t_cylinder *cy, t_plane *pl,
				t_cone *cn);
t_world		*ft_new_world(t_sp *sp, t_plane *pl, t_cone *cn, t_cylinder *cy);
void		ft_free_world(t_world **world);
void		ft_free_spheres(t_sp *sp);
#endif
