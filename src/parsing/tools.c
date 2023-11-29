/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 13:04:12 by svan-has      #+#    #+#                 */
/*   Updated: 2023/11/27 12:47:26 by yizhang       ########   odam.nl         */
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

void	count_objects(char *file, t_data *data)
{
	int		rt_file;
	char	*line;

	rt_file = open (file, O_RDONLY);
	if (rt_file < 0)
		error_exit("Cannot open file");
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

float	string_to_float(char *string)
{
	int		i;
	bool	decimal_point;
	float	result;
	char	*number;

	input_check(string);
	result = 0;
	decimal_point = false;
	i = 0;
	while (string[i])
	{
		if (string[i] == '.')
		{
			decimal_point = true;
			break ;
		}
		i++;
	}
	if (decimal_point)
		result = devide_decimal(ft_atof(string + i + 1));
	number = null_check(ft_substr(string, 0, i));
	result += ft_atof(number);
	free(number);
	return (result);
}
