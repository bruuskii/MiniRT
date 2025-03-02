/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:23:21 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/02 17:01:28 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "display/display.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/libft.h"
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

void		ft_display_scene(t_scene *scene, t_win *data);
void		put_pixel_to_image(char *img_data, int x, int y, int color);
void		render_scene(void *img, t_scene *scene, t_world *world);
void		render_scene_cn_rows(t_scene *scene, char *img_data, int y,
				t_cone *cone);
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
void		ft_display(t_win *w, t_scene *scene);
int			ft_isdigit(int c);
char		*ft_strdup(const char *s1);
char		*ft_strtrim(char const *s1, char const *set);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);
char		**ft_lines(char *filename);
char		**ft_fullsplit(char const *s);
void		ft_add_back(t_sp **objs, t_sp *node);

t_vctr		*vct_sub(t_vctr *v1, t_vctr *v2);
double		ft_magnitude(t_vctr vec);
t_cam		*ft_cam(char **lst);
t_sp		*ft_obj(char **lst, int fl);
t_scene		*ft_scene(char **lst, int fl);
t_scene		*data_input(char *s, int fl);
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
t_ray		*get_ray(t_scene *scene, double x, double y);
t_vctr		ft_final_color(t_ray *ray, t_hit *hit, t_scene *scene,
				t_material *mtrl);
void		render_scene_cy_rows(t_scene *scene, char *img_data, int y,
				t_cylinder *cy);
t_hit		*ft_get_hit(t_ray *ray, t_world *world);
void		fill_color(t_helpers h);
t_vctr		calculate_chess_pattern(t_hit hit);
t_hit		*ft_innit_hit(t_ray *ray, t_world *tp);
void		ft_free_hit_elems(t_hit *hit);
void		ft_free_scene_utils(t_hit *hit, t_ray *ray);
void		ft_get_hit_color(t_world *world, t_hit *hit);
void		ft_innit_hit_sp(t_ray *ray, t_world *tp, t_hit **hit);
void		ft_innit_hit_pl(t_ray *ray, t_world *tp, t_hit **hit);
void		ft_innit_hit_cy(t_ray *ray, t_world *tp, t_hit **hit);
void		ft_innit_hit_cn(t_ray *ray, t_world *tp, t_hit **hit);
int			create_trgb(int t, int r, int g, int b);
void		render_scene_rows(t_scene *scene, char *img_data, int y,
				t_world *world);
void		ft_check_txtr(int fl, t_vctr *color_1, t_vctr *color_2);
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