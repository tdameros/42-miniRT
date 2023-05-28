__kernel void raytracer(__global unsigned int* image, int color) {
	int id = get_global_id(0);
	image[id] = color;
}
