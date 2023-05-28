typedef struct s_vector3f
{
	float	x;
	float	y;
	float	z;
}	t_vector3f;

__kernel void raytracer(__global unsigned int* image, t_vector3f color) {
	int id = get_global_id(0);
	image[id] = ((unsigned int)color.x << 16) | ((unsigned int)color.y << 8)
		| (unsigned int)color.z;
}
