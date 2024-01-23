#include "../minirt.h"
#include "../lib/libft/includes/libft.h"

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
            
			data->viewport[v] = init_camera(data, j, i);
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

void reset_pix(t_data *data)
{
	int v;
	int j;
	int i;

	v = 0;
	j = 0;
	while (j < data->viewport_w)
	{
		i = 0;
		while (i <data->viewport_h)
		{
			data->all_pix[v] = set_pixel(data->all_ray[v], j, i, 255);
			v++;
			i++;
		}
		j++;
	}
}


void    rotate_object(t_data *data, int axis, float value)
{
    t_quat  rotate;

    // if (data->rotation.obj_type == light)
    //     return ;
    // if (axis == x_axis)
    //     data->rotation.object->beta = value;
    // if (axis == y_axis)
    //     data->rotation.object->gamma = value;
    rotate = set_quat(0, 0, 0, 0);

    if (data->rotation.obj_type == light)
        return ;
    if (axis == x_axis)
        rotate = set_quat(cos(value), 0, sin(value), 0);
    if (axis == y_axis)
        rotate = set_quat(cos(value), sin(value), 0, 0);
    // printf("x: %f y: %f\n", data->rotation.object->vec2.x, data->rotation.object->vec2.y);
    if (data->rotation.obj_type == object && (axis == x_axis || axis == y_axis))
    {
        // t_vec y_rot = y_rotation(data->rotation.object->vec2, data->rotation.object->beta);
        // t_vec z_rot = z_rotation(y_rot, data->rotation.object->alpha);
        // t_vec x_rot = x_rotation(z_rot, data->rotation.object->gamma);
        // data->rotation.object->vec2 = x_rot;
        
        // if (axis == x_axis)
        //     rotate = set_quat(cos(value), 0, sin(value), 0);
        // else if (axis == y_axis)
        //     rotate = set_quat(cos(value), sin(value), 0, 0);
        // // if (value > 0)
        // //     rotate = rev_rotate(rotate);

        // t_vec euler_angles = set_vec(data->rotation.object->gamma, data->rotation.object->alpha, 0);
        // t_vec axis = unit_vector(euler_angles);
        // float angle = vec_len(euler_angles);

        // rotate = axis_angle_to_quaternion(axis, angle);
        // rotate = set_quat(cos(value), 0, sin(value), 0);
        // t_quat rot2 = rotate = set_quat(cos(data->rotation.object->alpha), sin(data->rotation.object->alpha), 0, 0);
        // rotate.a += rot2.a;
        // rotate.b += rot2.b;
        // rotate.c += rot2.c;
        // rotate.d += rot2.d;  
        // t_quat


        data->rotation.object->vec2 = rotate_vector(data->rotation.object->vec2, rotate);
        // data->rotation.object->vec2 = rotate_vector_yaw_pitch_roll(data->rotation.object->vec2, data->rotation.object->beta, data->rotation.object->alpha, data->rotation.object->gamma);
      

    }
    if (data->rotation.obj_type == camera && (axis == x_axis || axis == y_axis))
    {
        if (axis == x_axis)
            data->camera.ovec.x += value;
        if (axis == y_axis)
            data->camera.ovec.y += value;
        if (axis == z_axis)
            data->camera.ovec.z += value;
    }
    reset_pix(data);
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
    reset_pix(data);
    calc_viewport(data);
	print_pix(data);
}

void    moving_keys(mlx_key_data_t kd, t_data *data)
{
    kd.key = 0;
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
        data->rotation.action(data, x_axis, -0.3);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
        data->rotation.action(data, x_axis, 0.3);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
        data->rotation.action(data, y_axis, -0.3);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_W))
        data->rotation.action(data, y_axis, 0.3);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
        data->rotation.action(data, z_axis, -0.3);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_E))
        data->rotation.action(data, z_axis, 0.3);
}

void    print_message(t_data *data, char *message)
{
    mlx_delete_image(data->mlx, data->img);
    data->img = mlx_new_image(data->mlx, data->viewport_w, data->viewport_h);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	print_pix(data);
    mlx_put_string(data->mlx, message, 0, 0);
}
void    change_object(t_data *data, int type, t_object *obj)
{
    char    *object;
    char    *object_id;

    data->rotation.obj_type = type;
    if (type == camera)
        print_message(data, "Changed to camera");
    else if (type == light)
        print_message(data, "Changed to light");
    else
    {
        if (obj)
            data->rotation.object = obj;
        object_id = ft_itoa(data->rotation.object->id + 1);
        object = ft_strjoin("Changed to object ", object_id);
        print_message(data, object);
        free(object);
        free(object_id);
    }
    
}
void    control_keys(mlx_key_data_t kd, t_data *data)
{
    kd.key = 0;
    if (mlx_is_key_down(data->mlx, MLX_KEY_R))
    {
        data->rotation.action = rotate_object;
        print_message(data, "Action: Rotation");
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_T))
    {
        data->rotation.action = translate_object;
	    print_message(data, "Action: Translation");
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_C))
        change_object(data, camera, NULL);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_L))
        change_object(data, light, NULL);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_O))
    {
        if (data->rotation.obj_type != object)
            change_object(data, object, NULL);
        else if ((data->rotation.object->id + 1) < data->object_num)
            change_object(data, object, &data->objects[data->rotation.object->id + 1]);
        else
            change_object(data, object, &data->objects[0]);
    }
}
void	key_press(mlx_key_data_t kd, void *param)
{
    t_data	*data;

	data = param;
    moving_keys(kd, data);
    control_keys(kd,data);
}


t_vec   rotate_vector(t_vec vec, t_quat r)
{
    t_vec   rotated_vector;
    t_quat  vec_quat;
    t_quat  rot_quat;

    vec_quat = set_quat(0, vec.x, vec.y, vec.z);
    rot_quat = set_quat(
        r.a * vec_quat.a - r.b * vec_quat.b - r.c * vec_quat.c - r.d * vec_quat.d,
        r.a * vec_quat.b + r.b * vec_quat.a + r.c * vec_quat.d - r.d * vec_quat.c,
        r.a * vec_quat.c - r.b * vec_quat.d + r.c * vec_quat.a + r.d * vec_quat.b,
        r.a * vec_quat.d + r.b * vec_quat.c - r.c * vec_quat.b + r.d * vec_quat.a
    );
    rot_quat = unit_quat(rot_quat);
    rotated_vector = set_vec(rot_quat.b, rot_quat.c, rot_quat.d);
    return (rotated_vector);
}