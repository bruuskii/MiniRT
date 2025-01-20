#include "../miniRT.h"

void	ft_checker(t_hit *hit, t_vctr original_normal)
{
	double	bump_intensity;
	double	noise_x;
	double	noise_y;
	double	noise_z;
	t_vctr	noise_offset;

	bump_intensity = 0.1;
	noise_x = fmod(sin(hit->point.x * 10), 1.0);
	noise_y = fmod(cos(hit->point.y * 10), 1.0);
	noise_z = fmod(tan(hit->point.z * 10), 1.0);
	noise_offset = (t_vctr){noise_x * bump_intensity, noise_y * bump_intensity,
		noise_z * bump_intensity};
	hit->normal = vec3_normalize(vec3_add(original_normal, noise_offset));
}
