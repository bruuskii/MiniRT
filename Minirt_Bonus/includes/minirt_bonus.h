#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "../libx/mlx.h"
# include <math.h> 
# include <stdio.h>
# include <stdlib.h>
#include  <fcntl.h>
#include "../libft/get_next_line/get_next_line.h"


#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1080


typedef enum    s_type
{
    SPHERE,
    PLANE,
    CYLINDRE,
    LIGHT,
    ALIGHT,
    CAM,
}               t_type;

typedef struct s_vec3
{
    double x;
    double y;
    double z;
} t_vec3;

typedef struct s_ray
{
    t_vec3 *origin;
    t_vec3 *direction;
} t_ray;

typedef struct s_camera
{
    t_vec3 *position;
    t_vec3 *direction;
    t_type          type;
    double fov;
} t_camera;


typedef struct s_material
{
    t_vec3 *color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
} t_material;

typedef struct s_light
{
    t_vec3 *position;
    t_vec3 *color;
    t_type          type;
    struct s_light  *next;
    double intensity;
} t_light;

typedef struct s_sphere
{
    t_vec3 *center;
    double radius;
    t_material *material;
} t_sphere;


typedef struct s_obj
{
    t_type         type;
    void           *obj;
    struct s_obj   *next;
}               t_obj;

typedef struct s_scene
{
    t_camera *camera;
    t_sphere *sphere;
    t_obj   *obj;
    t_light *light;
    t_vec3 *ambient_light;
    t_type         type;
    float ratio;
} t_scene;

typedef struct s_hit
{
    int hit;
    double t;
    t_vec3 *point;
    t_vec3 *normal;
} t_hit;


typedef struct s_data {
    void *mlx;
    void *win;
} t_data;

typedef struct s_plane
{
    t_vec3  *point;
    t_vec3  *normal;
    t_material *color;
}               t_plane;

typedef struct s_cylinder
{
    t_vec3  *c_cntr;
    t_vec3  *c_axis;
    double  d;
    double  height;
    t_material *color;
}               t_cylinder;


t_vec3 *vec3_create(double x, double y, double z);
t_ray *create_ray(t_camera *camera, double u, double v);
t_hit *intersect_sphere(t_ray *ray, t_sphere *sphere);
t_vec3 *calculate_lighting(t_ray *ray, t_vec3 *hit_point, t_vec3 *normal, t_scene *scene, t_material *material);
t_vec3 *phong_lighting(t_vec3 *light_dir, t_vec3 *view_dir, t_vec3 *normal, t_material *material, t_light *light); 

t_vec3 *vec3_add(t_vec3 *v1, t_vec3 *v2);
t_vec3 *vec3_sub(t_vec3 *v1, t_vec3 *v2);
t_vec3 *vec3_scale(t_vec3 *v, double t);
t_vec3 *vec3_cross(t_vec3 *v1, t_vec3 *v2);
double vec3_dot(t_vec3 *v1, t_vec3 *v2);
t_vec3 *vec3_normalize(t_vec3 *v);



// To organaize
int	        ft_isdigit(int c);
char	    *ft_strdup(const char *s1);
char	    *ft_strtrim(char const *s1, char const *set);
int	        ft_strcmp(const char *s1, const char *s2);
size_t	    ft_strlen(const char *s);
int         ft_check_extention(char *s);
int         ft_check_args(int ac);
char        **ft_lines(char *filename);
char	    **ft_fullsplit(char const *s);
int	        ft_is_void(char c);
t_obj       *ft_new(void *contenT);
void        ft_add_back(t_obj **objs, t_obj *node);
void	    ft_lstfree(char **lst);
char	    **ft_split(char const *s, char c);
double	    ft_atodbl(char *str);
double	    ft_atoi(char *str);
void        ft_assign_plane(t_plane *pl, char **lst);
void        ft_assign_cy(t_cylinder *cy, char **lst);
void        ft_assign_sp(t_sphere *sp, char **lst);
void        ft_assign_plane_utils(t_plane **pl, char **tmp, int i);
void        ft_assign_cy_utils(t_cylinder **cy, char **lst, int i);
void        ft_assign_sp_utils(t_sphere **sp, char **tmp, int i);
double      ft_magnitude(t_vec3 *vec);
void        ft_assign_camera(t_camera *cam, char **lst);
void        ft_assign_cam_utils(t_camera **cam, char **tmp, int i);
t_camera       *ft_cam(char **lst);
t_obj       *ft_obj(char **lst);
t_scene     *ft_scene(char **lst);
t_scene     *data_input(char *s);
void        ft_assign_light_utils(t_light **lt, char **lst, int i);
void        ft_assign_light(t_light *lt, char **lst);
t_light     *ft_light(char **lst);
void        ft_add_back_lt(t_light **objs, t_light *node);
t_light     *ft_new_lt();
t_scene    *ft_a_light();
void        ft_assign_alight_utils(t_scene **lt, char **lst, int i);
void        ft_assign_alight(t_scene *lt, char **lst);
t_scene    *ft_alight(char **lst);
#endif