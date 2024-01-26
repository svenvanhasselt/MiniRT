/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/26 10:34:01 by svan-has      #+#    #+#                 */
/*   Updated: 2024/01/26 15:37:18 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"

t_quat	set_quat(float a, float b, float c, float d)
{
	t_quat	new;

	new.a = a;
	new.b = b;
	new.c = c;
	new.d = d;
	return (new);
}

void	reset_pix(t_data *data)
{
	int	v;
	int	j;
	int	i;

	v = 0;
	j = 0;
	while (j < data->viewport_w)
	{
		i = 0;
		while (i < data->viewport_h)
		{
			data->all_pix[v] = set_pixel(data->all_ray[v], j, i, 255);
			v++;
			i++;
		}
		j++;
	}
}

t_quat	unit_quat(t_quat q)
{
	float	norm;

	norm = sqrt(q.a * q.a + q.b * q.b + q.c * q.c + q.d * q.d);
	q.a /= norm;
	q.b /= norm;
	q.c /= norm;
	q.d /= norm;
	return (q);
}

void	change_type(t_data *data, int type, t_object *obj)
{
	char	*object;
	char	*object_id;

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

void	init_rotation(t_data *data)
{
	data->rotation.action = translation;
	data->rotation.object = &data->objects[0];
	data->rotation.obj_type = object;
}
