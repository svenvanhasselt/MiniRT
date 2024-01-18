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

void    calc_viewport(t_data *data)
{
    int		v;
	int		j;
	int		i;

    v = 0;
	j = 0;
    while (j < data->viewport_w)
	{
		i = 0;
		while (i <data->viewport_h)
		{
			data->viewport[v] = set_vec(data->camera.vec.x - data->viewport_w/2 + j, data->camera.vec.y + data->viewport_h/2 - i, data->camera.focal_length);
			data->all_ray[v] = set_ray(data->camera.vec, data->viewport[v]);
			hit_object(data, v);
			if (data->all_ray[v].t > 0)
			{
				t_vec color = ray_color(data->all_ray[v], data->all_ray[v].t, data->all_ray[v].obj, data);
				data->all_pix[v] = set_pixel(data->all_ray[v], j, i, get_rgba(color.x,color.y,color.z));
			}
			if (v >= data->ray_pix_num)
				break;
			v++;
			i++;
		}
		j++;
	}
}
t_quat  set_quat(float a, float b, float c, float d)
{
    t_quat  new;

    new.a = a;
    new.b = b;
    new.c = c;
    new.d = d;
    return (new);
}
void    rotate_object(t_data *data, int axis, float value)
{
    t_quat  rotate;

    rotate = set_quat(0, 0, 0, 0);
    if (data->rotation.obj_type == object)
    {
        if (axis == x_axis)
            rotate = set_quat(cos(value), 0, sin(value), 0);
        else if (axis == y_axis)
            rotate = set_quat(cos(value * 3), sin(value * 3), 0, 0);
        if (value < 0)
            rev_rotate(rotate);
        data->rotation.object->vec2 = rotate_vector(data->rotation.object->vec2, rotate);
    }
    calc_viewport(data);
	print_pix(data);
}

void    translate_object(t_data *data, int axis, float value)
{
    if (data->rotation.obj_type == camera)
    {
        if (axis == x_axis)
            data->camera.vec.x += value;
        else if (axis == y_axis)
            data->camera.vec.y += value;
        else if (axis == z_axis)
            data->camera.vec.z += value;    
    }
    else if (data->rotation.obj_type == light)
    {
        if (axis == x_axis)
            data->light.vec.x += value * 10;
        else if (axis == y_axis)
            data->light.vec.y += value * 10;
        else if (axis == z_axis)
            data->light.vec.z += value * 10;    
    }
    else if (data->rotation.obj_type == object)
    {
        if (axis == x_axis)
            data->rotation.object->vec.x += value;
        else if (axis == y_axis)
            data->rotation.object->vec.y += value;
        else if (axis == z_axis)
            data->rotation.object->vec.z += value;
    }
    calc_viewport(data);
	print_pix(data);
}

void    moving_keys(mlx_key_data_t kd, t_data *data)
{
    kd.key = 0;
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
        data->rotation.action(data, x_axis, -0.1);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
        data->rotation.action(data, x_axis, 0.1);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
        data->rotation.action(data, y_axis, -0.1);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_W))
        data->rotation.action(data, y_axis, 0.1);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
        data->rotation.action(data, z_axis, -0.1);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_E))
        data->rotation.action(data, z_axis, 0.1);
}

void    control_keys(mlx_key_data_t kd, t_data *data)
{
    kd.key = 0;
    if (mlx_is_key_down(data->mlx, MLX_KEY_R))
        data->rotation.action = rotate_object;
    else if (mlx_is_key_down(data->mlx, MLX_KEY_T))
        data->rotation.action = translate_object;
    else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_C))
        data->rotation.obj_type = camera;
    else if (mlx_is_key_down(data->mlx, MLX_KEY_L))
          data->rotation.obj_type = light;
    else if (mlx_is_key_down(data->mlx, MLX_KEY_O))
    {
        if (data->rotation.obj_type != object)
            data->rotation.obj_type = object;
        else if (data->rotation.object->id + 1 < data->object_num - 1)
            data->rotation.object = &data->objects[data->rotation.object->id + 1];
        else
            data->rotation.object = &data->objects[0];
    }
}
void	key_press(mlx_key_data_t kd, void *param)
{
    t_data	*data;

	data = param;
    moving_keys(kd, data);
    control_keys(kd,data);

}


t_quat  unit_quat(t_quat q)
{
    float   norm;
    
    norm = sqrt(q.a * q.a + q.b * q.b + q.c * q.c + q.d * q.d);
    q.a /= norm;
    q.b /= norm;
    q.c /= norm;
    q.d /= norm;
    return (q);
}

t_vec   rotate_vector(t_vec vec, t_quat rotation)
{
    t_vec   rotated_vector;
    t_quat  vector_quaternion;
    t_quat  rotated_quat;

    vector_quaternion = set_quat(0, vec.x, vec.y, vec.z);
    rotated_quat = set_quat(
        rotation.a * vector_quaternion.a - rotation.b * vector_quaternion.b - rotation.c * vector_quaternion.c - rotation.d * vector_quaternion.d,
        rotation.a * vector_quaternion.b + rotation.b * vector_quaternion.a + rotation.c * vector_quaternion.d - rotation.d * vector_quaternion.c,
        rotation.a * vector_quaternion.c - rotation.b * vector_quaternion.d + rotation.c * vector_quaternion.a + rotation.d * vector_quaternion.b,
        rotation.a * vector_quaternion.d + rotation.b * vector_quaternion.c - rotation.c * vector_quaternion.b + rotation.d * vector_quaternion.a
    );
    rotated_vector = set_vec(rotated_quat.b, rotated_quat.c, rotated_quat.d);
    return (rotated_vector);
}