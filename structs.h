/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:45:14 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/24 18:25:34 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define HEIGHT 800
# define WIDTH 800
# define ERROR_MESSAGE "Error\n"
# define M_W 200
# define M_H 200
# define M_H_00 50

typedef enum s_type
{
	SPHERE,
	PLANE,
	CYLINDRE,
	LIGHT,
	ALIGHT,
	CONE,
	CAM,
}						t_type;

typedef struct s_win
{
	int					height;
	int					width;
	void				*ptr;
	void				*win;
	void				*img;
}						t_win;

typedef struct s_vctr
{
	double				x;
	float				y;
	float				z;
}						t_vctr;

typedef struct s_material
{
	t_vctr				color;
	double				ambient;
	double				diffuse;
	double				specular;
	double				shininess;
}						t_material;

typedef struct s_light
{
	t_vctr				*dir;
	double				brightness;
	t_vctr				*color;
	t_type				type;
	struct s_light		*next;
}						t_light;

typedef struct s_alight
{
	float				ratio;
	t_type				type;
	t_vctr				*color;
}						t_alight;

typedef struct s_sp
{
	double				d;
	t_material			*mtrl;
	t_vctr				*cntr;
	t_vctr				*color;
	int					fl;
	int					chess;
	int					id;
	struct s_sp			*next;

}						t_sp;

typedef struct s_plane
{
	t_vctr				*point;
	t_vctr				*normal;
	t_material			*mtrl;
	int					fl;
	t_vctr				*color;
	struct s_plane		*next;
	int					chess;
}						t_plane;

typedef struct s_cylinder
{
	t_vctr				*c_cntr;
	t_vctr				*c_axis;
	t_material			*mtrl;
	double				d;
	int					fl;
	double				height;
	t_vctr				*color;
	struct s_cylinder	*next;
	int					chess;
}						t_cylinder;

typedef struct s_obj
{
	t_type				type;
	t_material			*mtrl;
	void				*obj;
	struct s_obj		*next;
}						t_obj;

typedef struct s_cam
{
	t_vctr				*pos;
	t_vctr				*dir;
	t_type				type;
	double				fov;
}						t_cam;

typedef struct s_scene
{
	struct s_cam		*cam;
	struct s_sp			*sp;
	struct s_plane		*pl;
	struct s_cylinder	*cy;
	struct s_light		*light;
	struct s_alight		*alight;
	struct s_cone		*cn;
}						t_scene;

typedef struct s_ray
{
	t_vctr				origin;
	t_vctr				direction;
}						t_ray;

typedef struct s_camera
{
	t_vctr				position;
	t_vctr				direction;
	double				fov;
}						t_camera;

typedef struct s_cone
{
	t_vctr				*vertex;
	t_vctr				*axis;
	t_vctr				*color;
	double				tang;
	double				minm;
	double				maxm;
	t_material			*mtrl;
	struct s_cone		*next;
}						t_cone;

typedef struct s_hit
{
	int					hit;
	double				shaddow;
	double				t;
	t_vctr				point;
	t_vctr				normal;
}						t_hit;

typedef struct s_data
{
	void				*mlx;
	void				*win;
}						t_data;

typedef struct s_view
{
	t_vctr				light_dir;
	t_vctr				view_dir;
	t_light				*light;
	t_ray				*ray;

}						t_view;

typedef struct s_cone_data
{
	t_vctr				co;
	t_vctr				v;
	double				k;
	double				a;
	double				b;
	double				discriminant;
}						t_cone_data;

typedef struct s_helpers
{
	double				u;
	double				v;
	int					square_u;
	int					square_v;
	int					square_x;
	int					square_y;
	double				angle;
	double				height;
	int					square_angle;
	int					square_height;
	double				radius;
	t_vctr				pattern_color;
	t_vctr				white;
	t_vctr				black;
	t_vctr				ambient;
	t_vctr				shadowed;
	t_hit				*lol;
	t_hit				hit_point;
	t_ray				raysh;
	t_vctr				normal;
	t_hit				hit;
	int					in_shadow;
	t_vctr				color;
}						t_helpers;

#endif