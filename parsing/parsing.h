/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:01:32 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/27 23:22:52 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../structs.h"

void		ft_assign_alight(t_alight *lt, char **lst);
void		ft_assign_cone(t_cone *cn, char **lst);
int			is_valid_str(char *s);
int			valid_syntax(char **lst);
void		ft_assign_plane_point(t_plane **pl, char *lst);
void		ft_assign_plane_color(t_plane **pl, char *lst);
void		ft_assign_plane_normal(t_plane **pl, char *lst);
void		ft_assign_plane_utils(t_plane **pl, char **lst, int i);
void		ft_assign_cy_center(t_cylinder **cy, char *s);
void		ft_assign_cy_axis(t_cylinder **cy, char *s);
void		ft_assign_cy_utils_color(t_cylinder **cy, char *s);
void		ft_assign_cy_utils(t_cylinder **cy, char **lst, int i);
void		ft_assign_sp_center(t_sp **sp, char *lst);
void		ft_assign_sp_utils_color(t_sp **sp, char *lst);
void		ft_assign_sp_utils(t_sp **sp, char **lst, int i);
void		ft_assign_cam_utils_pos(t_cam **cam, char *lst);
void		ft_assign_cam_utils_dir(t_cam **cam, char *lst);
void		ft_assign_cam_utils(t_cam **cam, char **lst, int i);
void		ft_assign_light_dir(t_light **lt, char *s);
void		ft_assign_light_color(t_light **lt, char *s);
void		ft_assign_light_utils(t_light **lt, char **lst, int i);
void		ft_assign_alight_color(t_alight **lt, char *s);
void		ft_assign_alight_utils(t_alight **lt, char **lst, int i);
void		ft_assign_cn_vertex(t_cone **cn, char *s);
void		ft_assign_cn_color(t_cone **cn, char *s);
void		ft_assign_cn_axis(t_cone **cn, char *lst);
void		ft_assign_cn_tang(t_cone **cn, char *s);
void		ft_assign_cn_utils(t_cone **cn, char **lst, int i);
void		ft_assign_plane(t_plane *pl, char **lst);
void		ft_assign_cy(t_cylinder *cy, char **lst);
void		ft_assign_sp(t_sp *sp, char **lst);
void		ft_assign_camera(t_cam *cam, char **tmp);
void		ft_assign_light(t_light *lt, char **lst);
int			ft_check_extention(char *s);
int			ft_check_args(int ac);
int			ft_check_first_param(char *s);
int			ft_read_lines_from_file(char *filename);
int			ft_count_line(char *filename);
void		ft_line_utils(int *c, int fd, char **lst);
char		**ft_lines(char *filename);
int			ft_lst_count(char **lst);
void		ft_assign_cone_ptr(char **tmp, t_cone **lt, int fl);
t_cone		*ft_cone(char **lst, int fl);
void		ft_assign_flag_sphere(int n, char **tmp, t_sp *node, int fl);
void		ft_assign_sphere(char **tmp, t_sp **lt, int n, int fl);
t_sp		*ft_obj(char **lst, int fl);
void	    ft_assign_ptr_plane(char **tmp, t_plane **lt, int fl);
t_plane		*ft_obj_pl(char **lst, int fl);
void		ft_assign_cy_ptr(char **tmp, t_cylinder **lt, int fl);
t_cylinder	*ft_obj_cy(char **lst, int fl);
void		ft_process_cam(char *entry, t_cam **ptr, int *c);
t_cam		*ft_cam(char **lst);
void		ft_process_light(char *entry, t_light **lt, int *c);
t_light		*ft_light(char **lst);
void		ft_alight_ptr(int *c, char **tmp, t_alight **node);
t_alight	*ft_alight(char **lst);
t_scene		*ft_scene(char **lst, int fl);
t_scene		*data_input(char *s, int fl);
void		ft_free_scene(t_scene *scene);
void		ft_swap_circle(t_sp *a, t_sp *b);

void		swap_planes(t_plane *a, t_plane *b);

void		swap_cylinders(t_cylinder *a, t_cylinder *b);

void		swap_cones(t_cone *a, t_cone *b);
void		ft_assign_world_to_scene(t_world **world, char **lst, int fl);
#endif