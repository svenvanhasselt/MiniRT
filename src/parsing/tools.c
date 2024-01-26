/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 13:04:12 by svan-has      #+#    #+#                 */
/*   Updated: 2024/01/26 15:26:09 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"
#include <fcntl.h>

void	replace_char(char **string, char a, char b)
{
	int	i;

	i = 0;
	while ((*string)[i])
	{
		if ((*string)[i] == a)
			(*string)[i] = b;
		i++;
	}
}

void	count_objects(t_data *data, int rt_file)
{
	char	*line;

	while (1)
	{
		line = get_next_line(rt_file);
		if (!line)
			break ;
		if (line_check_object(line))
			data->object_num++;
		free(line);
	}
	data->objects = null_check(malloc (data->object_num * sizeof(t_object)));
	close(rt_file);
}

float	devide_decimal(float number)
{
	if ((int)number != 0)
		number = devide_decimal(number / 10);
	return (number);
}

float	check_v(float value, float min, float max)
{
	if (value < min || value > max)
		error_exit("Input data outside permitted value");
	return (value);
}
