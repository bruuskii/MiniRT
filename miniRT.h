/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:23:21 by kbassim           #+#    #+#             */
/*   Updated: 2025/02/23 11:46:17 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/get_next_line/get_next_line.h"
# include "parsing/parsing.h"
# include "structs.h"
# include "utils/utils.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

t_view		*ft_view(t_vctr light_dir, t_vctr view_dir, t_light *light,
				t_ray *ray);
void		render_scene_cn(void *img, t_scene *scene, t_cone *cone);
t_material	*ft_material(t_scene *scene, double dif, double spec, double sh);
void		ft_scene_cone(t_scene *scene, t_win *data, void *ptr);
void		ft_scene_cylinder(t_scene *scene, t_win *data, void *ptr);
void		ft_scene_plane(t_scene *scene, void *ptr, t_win *data);
void		ft_scene_sphere(t_scene *scene, void *ptr, t_win *data);
int			create_trgb(int t, int r, int g, int b);
void		ft_display_scene(t_scene *scene, t_win *data);
void		put_pixel_to_image(char *img_data, int x, int y, int color);
double		dgrs_to_rdn(double angle);
double		calculate_distance(double fov);
void		render_scene_plane(void *img, t_scene *scene, t_plane *pl);
void		render_scene_cy(void *img, t_scene *scene, t_cylinder *cy);
void		render_scene(void *img, t_scene *scene, t_world *world);
void		ft_render_sphere(t_sp **sphere, void *img, t_scene *scene);
void		render_scene_cn_rows(t_scene *scene, char *img_data, int y,
				t_cone *cone);
t_hit		*intersect_cone(t_ray *ray, t_cone *cone);
void		ft_print_and_exit(char *s, int stat);
int			ft_lst_count(char **lst);
t_hit		*intersect_cone(t_ray *ray, t_cone *cone);
t_vctr		vec3_create(double x, double y, double z);
t_cone		*ft_cone(char **lst, int fl);
t_hit		*intersect_sphere(t_ray *ray, t_sp *sphere);
t_ray		create_shadow_ray(t_hit hit, t_vctr point, t_light *light);
void		ft_assign_cone(t_cone *cn, char **lst);
void		ft_add_back_cn(t_cone **cn, t_cone *node);
void		ft_assign_cn_utils(t_cone **cn, char **lst, int i);
t_vctr		calculate_lighting(t_view *view, t_hit hit, t_scene *scene,
				t_material *material);
t_vctr		phong_lighting(t_view *view, t_vctr normal, t_material *material);
t_ray		create_nray(t_vctr point, t_vctr dir, double u, double v);
int			ft_is_shadowed(t_scene *scene, t_vctr *point, double u, double v);
t_vctr		vec3_add(t_vctr v1, t_vctr v2);
t_vctr		vec3_sub(t_vctr v1, t_vctr v2);
t_vctr		vec3_scale(t_vctr v, double t);
t_vctr		vec3_cross(t_vctr v1, t_vctr v2);
double		vec3_dot(t_vctr v1, t_vctr v2);
t_vctr		vec3_normalize(t_vctr v);
t_hit		*intersect_plane(t_ray *ray, t_plane *plane);
t_hit		*intersect_cylinder(t_ray *ray, t_cylinder *cy);
t_hit		*intersect_scene(t_ray *ray, t_scene *scene);
t_ray		*reflected_ray(t_hit *hit, t_ray *ray);
void		ft_free_all(t_scene **scene);
void		ft_free_win(t_win *win);
int			ft_escape_key(int key, void *param);
int			ft_close(t_win *param);
void		ft_display(t_win *w, t_scene *scene);
int			ft_isdigit(int c);
char		*ft_strdup(const char *s1);
char		*ft_strtrim(char const *s1, char const *set);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);
int			ft_check_extention(char *s);
int			ft_check_args(int ac);
char		**ft_lines(char *filename);
char		**ft_fullsplit(char const *s);
int			ft_is_void(char c);
void		ft_add_back(t_sp **objs, t_sp *node);
t_sp		*ft_new(t_sp *content);
t_plane		*ft_new_pl(t_plane *content);
t_plane		*ft_obj_pl(char **lst, int fl);
void		ft_add_back_pl(t_plane **objs, t_plane *node);
void		ft_lstfree(char **lst);
char		**ft_split(char const *s, char c);
double		ft_atodbl(char *str);
double		ft_atoi(char *str);
void		ft_assign_plane(t_plane *pl, char **lst);
void		ft_assign_cy(t_cylinder *cy, char **lst);
void		ft_assign_sp(t_sp *sp, char **lst);
void		ft_assign_plane_utils(t_plane **pl, char **tmp, int i);
void		ft_assign_cy_utils(t_cylinder **cy, char **lst, int i);
void		ft_assign_sp_utils(t_sp **sp, char **tmp, int i);
t_vctr		*vct_sub(t_vctr *v1, t_vctr *v2);
double		ft_magnitude(t_vctr vec);
void		ft_assign_camera(t_cam *cam, char **lst);
void		ft_assign_cam_utils(t_cam **cam, char **tmp, int i);
t_cam		*ft_cam(char **lst);
t_sp		*ft_obj(char **lst, int fl);
t_scene		*ft_scene(char **lst, int fl);
t_scene		*data_input(char *s, int fl);
void		ft_assign_light_utils(t_light **lt, char **lst, int i);
void		ft_assign_light(t_light *lt, char **lst);
t_light		*ft_light(char **lst);
void		ft_add_back_lt(t_light **objs, t_light *node);
t_light		*ft_new_lt(void);
t_alight	*ft_a_light(void);
void		ft_assign_alight_utils(t_alight **lt, char **lst, int i);
void		ft_assign_alight(t_alight *lt, char **lst);
t_alight	*ft_alight(char **lst);
void		ft_add_back_cy(t_cylinder **objs, t_cylinder *node);
t_cylinder	*ft_new_cy(t_cylinder *content);
t_cone		*ft_new_cone(t_cone *content);
double		ft_magnitude(t_vctr vec);
void		ft_free_cylinder(t_cylinder *c);
void		ft_free_scene(t_scene *scene);
int			ft_check_first_param(char *s);
void		ft_checker(t_hit *hit, t_vctr original_normal);
t_ray		*get_ray(t_scene *scene, double x, double y);
t_vctr		ft_final_color(t_ray *ray, t_hit *hit, t_scene *scene,
				t_material *mtrl);
void		render_scene_cy_rows(t_scene *scene, char *img_data, int y,
				t_cylinder *cy);
void		ft_checker_plane(t_hit *hit, t_vctr original_normal);
void		ft_chess_sphere(t_scene *scene, t_vctr color, t_vctr normal,
				t_material *material);
void		render_scene_rows(t_scene *scene, char *img_data, int y,
				t_world *world);
void		ft_assign_plane_mtrl(t_material *mtrl, t_plane **pl);
void		ft_assign_cylinder_mtrl(t_material *mtrl, t_cylinder **cy);
void		ft_assign_cone_mtrl(t_material *mtrl, t_cone **cn);
void		ft_assign_sphere_mtrl(t_material *mtrl, t_sp **sp);
t_hit		*ft_get_hit(t_ray *ray, t_world *world);
void		fill_color(t_helpers h);
t_vctr		calculate_chess_pattern(t_hit hit);
t_hit	*ft_innit_hit(t_ray *ray, t_world *tp);
void	ft_free_hit_elems(t_hit *hit);
void	ft_free_scene_utils(t_scene *scene, t_hit *hit, t_ray *ray);
void	ft_get_hit_color(t_world *world, t_hit *hit);
t_hit	*ft_get_hit(t_ray *ray, t_world *world);
void	ft_innit_hit_sp(t_ray *ray, t_world *tp, t_hit **hit);
void	ft_innit_hit_pl(t_ray *ray, t_world *tp, t_hit **hit);
void	ft_innit_hit_cy(t_ray *ray, t_world *tp, t_hit **hit);
void	ft_innit_hit_cn(t_ray *ray, t_world *tp, t_hit **hit);
// bonus
void		ft_render_sphere_bonus(t_hit *hit);
void		ft_render_plane_bonus_utils(t_hit *hit, t_plane *pl, t_helpers *h);
void		ft_render_plane_bonus(t_hit *hit);
void		ft_render_cylinder_bonus(t_hit *hit);
void		ft_render_cone_bonus(t_hit *hit);
t_vctr		rgb_to_color(unsigned int color);
void		ft_assign_txtr_sp(t_world *tp);
void		ft_assign_txtr_pl(t_world *tp);
void		ft_assign_txtr_cy(t_world *tp);
void		ft_assign_txtr_cn(t_world *tp);
void		ft_assign_txtrs(t_world **world);
void		ft_assign_fl_sp(t_world *tp);
void		ft_assign_fl_pl(t_world *tp);
void		ft_assign_fl_cy(t_world *tp);
void		ft_assign_fl_cn(t_world *tp);
void		ft_assign_fl(t_world *world);
#endif