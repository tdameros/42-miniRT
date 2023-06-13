#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "libft.h"
#include "mlx.h"

#include "gui/init.h"
#include "events.h"
#include "parsing.h"
#include "hooks.h"
#include "render_frame.h"
#include "window.h"
#include "engine.h"
#include "colors.h"
#include "opencl_kernel_names.h"

const char *ft_cl_getErrorString(cl_int error)
{
	switch(error){
		// run-time and JIT compiler errors
		case 0: return "CL_SUCCESS";
		case -1: return "CL_DEVICE_NOT_FOUND";
		case -2: return "CL_DEVICE_NOT_AVAILABLE";
		case -3: return "CL_COMPILER_NOT_AVAILABLE";
		case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
		case -5: return "CL_OUT_OF_RESOURCES";
		case -6: return "CL_OUT_OF_HOST_MEMORY";
		case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
		case -8: return "CL_MEM_COPY_OVERLAP";
		case -9: return "CL_IMAGE_FORMAT_MISMATCH";
		case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
		case -11: return "CL_BUILD_PROGRAM_FAILURE";
		case -12: return "CL_MAP_FAILURE";
		case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
		case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
		case -15: return "CL_COMPILE_PROGRAM_FAILURE";
		case -16: return "CL_LINKER_NOT_AVAILABLE";
		case -17: return "CL_LINK_PROGRAM_FAILURE";
		case -18: return "CL_DEVICE_PARTITION_FAILED";
		case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

		// compile-time errors
		case -30: return "CL_INVALID_VALUE";
		case -31: return "CL_INVALID_DEVICE_TYPE";
		case -32: return "CL_INVALID_PLATFORM";
		case -33: return "CL_INVALID_DEVICE";
		case -34: return "CL_INVALID_CONTEXT";
		case -35: return "CL_INVALID_QUEUE_PROPERTIES";
		case -36: return "CL_INVALID_COMMAND_QUEUE";
		case -37: return "CL_INVALID_HOST_PTR";
		case -38: return "CL_INVALID_MEM_OBJECT";
		case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
		case -40: return "CL_INVALID_IMAGE_SIZE";
		case -41: return "CL_INVALID_SAMPLER";
		case -42: return "CL_INVALID_BINARY";
		case -43: return "CL_INVALID_BUILD_OPTIONS";
		case -44: return "CL_INVALID_PROGRAM";
		case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
		case -46: return "CL_INVALID_KERNEL_NAME";
		case -47: return "CL_INVALID_KERNEL_DEFINITION";
		case -48: return "CL_INVALID_KERNEL";
		case -49: return "CL_INVALID_ARG_INDEX";
		case -50: return "CL_INVALID_ARG_VALUE";
		case -51: return "CL_INVALID_ARG_SIZE";
		case -52: return "CL_INVALID_KERNEL_ARGS";
		case -53: return "CL_INVALID_WORK_DIMENSION";
		case -54: return "CL_INVALID_WORK_GROUP_SIZE";
		case -55: return "CL_INVALID_WORK_ITEM_SIZE";
		case -56: return "CL_INVALID_GLOBAL_OFFSET";
		case -57: return "CL_INVALID_EVENT_WAIT_LIST";
		case -58: return "CL_INVALID_EVENT";
		case -59: return "CL_INVALID_OPERATION";
		case -60: return "CL_INVALID_GL_OBJECT";
		case -61: return "CL_INVALID_BUFFER_SIZE";
		case -62: return "CL_INVALID_MIP_LEVEL";
		case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
		case -64: return "CL_INVALID_PROPERTY";
		case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
		case -66: return "CL_INVALID_COMPILER_OPTIONS";
		case -67: return "CL_INVALID_LINKER_OPTIONS";
		case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

		// extension errors
		case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
		case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
		case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
		case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
		case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
		case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
		default: return "Unknown OpenCL error";
    }
}


static void	init_hooks(t_engine *minirt);

static int	init_opencl(t_opencl *opencl)
{
	cl_uint number_of_platforms;
	cl_int	return_code;
	cl_platform_id *platforms;

	return_code = clGetPlatformIDs(0, NULL, &number_of_platforms);
	if (return_code != CL_SUCCESS) {
		printf("clGetPlatformIDs() failed with error code %s\n", ft_cl_getErrorString(return_code));
		exit(1);
	}
	printf("number_of_platforms == %i\n", number_of_platforms);
	platforms = malloc(number_of_platforms * sizeof(cl_platform_id));
	if (platforms == NULL) {
		perror("Failed to allocate platforms");
		exit(1);
	}
	return_code = clGetPlatformIDs(number_of_platforms, platforms, NULL);
	// TODO secure stuff
	return_code = clGetDeviceIDs(*platforms, CL_DEVICE_TYPE_GPU, 1, &opencl->deviceID, NULL);
	if (return_code != CL_SUCCESS) {
		printf("clGetDeviceIDs() failed with error code %s\n", ft_cl_getErrorString(return_code));
		exit(1);
	}
	free(platforms);
	opencl->context = clCreateContext(NULL, 1, &opencl->deviceID, NULL, NULL, NULL);
	opencl->commandQueue = clCreateCommandQueue(opencl->context, opencl->deviceID, 0, NULL);
	return (0);
}

static int	init_raytracing_kernel(t_engine *engine)
{
	char	*kernel_file;

	kernel_file = ft_read_file_to_c_string(RAYTRACER_KERNEL);
	if (kernel_file == NULL)
	{
		perror("Failed to read kernel "RAYTRACER_KERNEL);
		return (-1);
	}
	engine->raytracing_program = clCreateProgramWithSource(engine->opencl.context, 1, (const char **)&kernel_file, NULL, NULL);
	free(kernel_file);
	clBuildProgram(engine->raytracing_program, 1, &engine->opencl.deviceID, NULL, NULL, NULL);

	cl_build_status buildStatus;
	clGetProgramBuildInfo(engine->raytracing_program, engine->opencl.deviceID, CL_PROGRAM_BUILD_STATUS, sizeof(cl_build_status), &buildStatus, NULL);

	if (buildStatus == CL_BUILD_ERROR)
	{
		size_t logSize;
		clGetProgramBuildInfo(engine->raytracing_program, engine->opencl.deviceID, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
		char* log = malloc(logSize);
		if (log != NULL)
			clGetProgramBuildInfo(engine->raytracing_program, engine->opencl.deviceID, CL_PROGRAM_BUILD_LOG, logSize, log, NULL);
		printf("Compilation failed:\n%s\n", log != NULL ? log : "Failed to allocate memory for compilation error message");
		free(log);
		return (-1);
	}
	engine->raytracing_kernel = clCreateKernel(engine->raytracing_program, "raytracer", NULL);
	return (0);
}

static void	print_scene_content(t_raytracing_data *raytracing_data);
int	init_engine(t_engine *engine, const char *start_up_scene)
{
	ft_bzero(engine, sizeof(*engine));
	init_opencl(&engine->opencl);
	engine->window.mlx = mlx_init();
	if (engine->window.mlx == NULL)
		return (-1);
	engine->window.window = mlx_new_window(engine->window.mlx, WINDOW_WIDTH,
										   WINDOW_HEIGHT, "miniRT");
	if (engine->window.window == NULL)
		return (-1); // TODO: free mlx
	if (parse_scene(engine, start_up_scene) < 0)
		return (-1); // TODO free stuff
	print_scene_content(&engine->raytracing_data);

	init_image(&engine->ray_traced_image, &engine->window, WINDOW_WIDTH, WINDOW_HEIGHT); // TODO secure me
	engine->ray_traced_image_gpu_buffer = clCreateBuffer(engine->opencl.context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY, engine->ray_traced_image.size * sizeof(unsigned int), NULL, NULL);

	init_image(&engine->main_image, &engine->window, WINDOW_WIDTH, WINDOW_HEIGHT); // TODO secure me
	change_image_color(&engine->main_image, COLOR_BLACK);

	init_hooks(engine);

	if (init_raytracing_kernel(engine) < 0)
		return (-1);
	if (init_gui_boxes(engine))
	{
		// TODO: free everything
		return (-1);
	}
	// TODO: secure me
	camera_create(&engine->camera, vector2f_create(WINDOW_WIDTH, WINDOW_HEIGHT));
	init_scene(&engine->scene);
	if (ttf_parser(&engine->gui.font,
				   "data/fonts/inconsolata/Inconsolata-VariableFont_wdth,wght.ttf")
		< 0)
//	if (ttf_parser(&minirt.gui.font,
//			"data/fonts/Envy Code R PR7/Envy Code R.ttf") < 0)
		return (-1); // TODO free everything

	return (0);
}

static void	init_hooks(t_engine *minirt)
{
	mlx_hook(minirt->window.window, KEY_PRESS, KEY_PRESS_MASK,
		&key_press_handler, minirt);
//	mlx_hook(minirt->window.window, KEY_RELEASE, KEY_RELEASE_MASK,
//		&key_release_handler, minirt);
	mlx_hook(minirt->window.window, BUTTON_PRESS, BUTTON_PRESS_MASK,
		&button_press_handler, minirt);
	mlx_hook(minirt->window.window, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
			 &close_engine, minirt);
	mlx_loop_hook(minirt->window.mlx, &render_frame, minirt);
}

static void print_color(t_color *color);
static void	print_vector(t_vector3f *vector);
static void	print_object(t_object *object);
#include <stdio.h>
static void	print_scene_content(t_raytracing_data *raytracing_data)
{
	printf("Ambient lightning\n");
	printf("\tAmbient lightning ratio == %f\n",
		raytracing_data->ambient_light.lighting_ratio);
	printf("\tAmbient lightning albedo\n");
	print_color(&raytracing_data->ambient_light.color);
	printf("Camera\n");
	printf("\tCamera position\n");
	print_vector(&raytracing_data->camera.position);
	printf("\tCamera orientation\n");
	print_vector(&raytracing_data->camera.direction);
	printf("\tCamera FOV == %f\n", raytracing_data->camera.vertical_fov);
	printf("Light\n");
	printf("\tLight position\n");
	print_vector(&raytracing_data->light.position);
	printf("\tLight brightness == %f\n", raytracing_data->light.brightness);
	printf("\tLight albedo\n");
	print_color(&raytracing_data->light.color);
	for (size_t i = 0; i < raytracing_data->objects.length; i++)
		print_object(&raytracing_data->objects.data[i]);
}

static void print_color(t_color *color)
{
	printf("\t\t\tr == %f\n", color->x);
	printf("\t\t\tg == %f\n", color->y);
	printf("\t\t\tb == %f\n", color->z);
}

static void	print_vector(t_vector3f *vector)
{
	printf("\t\t\tx == %f\n", vector->x);
	printf("\t\t\ty == %f\n", vector->y);
	printf("\t\t\tz == %f\n", vector->z);
}

static void	print_object(t_object *object)
{
	if (object->type == SPHERE)
		printf("Sphere\n");
	else if (object->type == PLANE)
		printf("Plane\n");
	else if (object->type == CYLINDER)
		printf("Cylinder\n");
	printf("\tPosition\n");
	print_vector(&object->position);
	printf("\tColor\n");
	print_color(&object->albedo);
	if (object->type == SPHERE || object->type == CYLINDER)
		printf("\tDiameter == %f\n", object->radius);
	if (object->type == CYLINDER)
		printf("\tHeight == %f\n", object->height);
	if (object->type == PLANE || object->type == CYLINDER)
	{
		printf("\tNormal\n");
		print_vector(&object->normal);
	}
}
