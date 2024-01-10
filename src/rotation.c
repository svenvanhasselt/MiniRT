#include "../minirt.h"

t_quat  rev_rotate(t_quat q)
{
    t_quat result;

    result.a = q.a;
    result.b = -q.b;
    result.c = -q.c;
    result.d = -q.d;
    return (result);
}
void	key_press(mlx_key_data_t kd, void *param)
{
    int		v;
	int		j;
	int		i;
	
	v = 0;
	j = 0;
    t_data	*data;
    float   value;

	data = param;
    value = M_PI / 180;
    if (kd.key == MLX_KEY_A)
    {
		data->gamma = value;
        t_quat rotate = {cos(data->gamma), 0, sin(data->gamma), 0};
        data->objects[1].vec2 = rotate_vector(data->objects[1].vec2, rotate);
    }
	if (kd.key == MLX_KEY_D)
    {
        data->gamma -= value;
        t_quat rotate = {cos(data->gamma), 0, sin(data->gamma), 0};
        rotate = rev_rotate(rotate);
        data->objects[1].vec2 = rotate_vector(data->objects[1].vec2, rotate);
    }
	if (kd.key == MLX_KEY_S)
		data->alpha += value;
    if (kd.key == MLX_KEY_W)
    {
		data->alpha += value;
        t_quat rotate = {cos(data->alpha), sin(data->alpha), 0, 0};
        data->objects[1].vec2 = rotate_vector(data->objects[1].vec2, rotate);
    }
    // mlx_delete_image(data->mlx, data->img);
    // data->img = mlx_new_image(data->mlx, data->viewport_w, data->viewport_h);
    // mlx_image_to_window(data->mlx, data->img, 0, 0);
	// data->objects[1].vec2 = rotate_vector(data->objects[1].vec2, rotate);
	// data->objects[1].vec2 = rotate_vector(data->objects[1].vec2, rotate);
	while (j < data->viewport_w)
	{
		i = 0;
		while (i <data->viewport_h)
		{
			data->viewport[v] = set_vec(data->camera.vec.x - data->viewport_w/2 + j, data->camera.vec.y + data->viewport_h/2 - i, data->camera.focal_length);
			data->all_ray[v] = set_ray(data->camera.vec, data->viewport[v]);
			hit_object(data, v);
			//printf("this is a obj:%i\n",  data->all_ray[v].obj->type);
			if (data->all_ray[v].t > 0)
			{	//will not go to other type of object
				//printf("this is a obj2:%i\n",  data->all_ray[v].obj->type);
				t_vec color = ray_color(data->all_ray[v], data->all_ray[v].t, data->all_ray[v].obj, data);
				data->all_pix[v] = set_pixel(data->all_ray[v], j, i, get_rgba(color.x,color.y,color.z));
			}
			//give_color(data, i, j, v);
			if (v >= data->ray_pix_num)
				break;
			v++;
			i++;
		}
		j++;
	}
	print_pix(data);
}


t_quat  unit_quat(t_quat q)
{
    float norm = sqrt(q.a * q.a + q.b * q.b + q.c * q.c + q.d * q.d);
    q.a /= norm;
    q.b /= norm;
    q.c /= norm;
    q.d /= norm;
    return (q);
}

t_vec   rotate_vector(t_vec vec, t_quat rotation)
{
    t_quat vector_quaternion = {0, vec.x, vec.y, vec.z};

    t_quat rotated_quat = {
        rotation.a * vector_quaternion.a - rotation.b * vector_quaternion.b - rotation.c * vector_quaternion.c - rotation.d * vector_quaternion.d,
        rotation.a * vector_quaternion.b + rotation.b * vector_quaternion.a + rotation.c * vector_quaternion.d - rotation.d * vector_quaternion.c,
        rotation.a * vector_quaternion.c - rotation.b * vector_quaternion.d + rotation.c * vector_quaternion.a + rotation.d * vector_quaternion.b,
        rotation.a * vector_quaternion.d + rotation.b * vector_quaternion.c - rotation.c * vector_quaternion.b + rotation.d * vector_quaternion.a
    };
    
    t_vec rotated_vector;
    rotated_vector.x = rotated_quat.b;
    rotated_vector.y = rotated_quat.c;
    rotated_vector.z = rotated_quat.d;
    return (rotated_vector);
}