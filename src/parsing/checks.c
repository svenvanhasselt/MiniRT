/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 14:57:54 by svan-has      #+#    #+#                 */
/*   Updated: 2023/11/17 11:03:22 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"

void	check_object_data(char *string, char ***split_line, \
t_data *data, int obj_index)
{
	int	len;

	len = ft_strlen(string);
	if (!ft_strncmp(string, "A", len))
		parse_amb_light(split_line, data);
	if (!ft_strncmp(string, "c", len))
		parse_camera(split_line, data);
	if (!ft_strncmp(string, "l", len))
		parse_light(split_line, data);
	if (len < 2)
		len = 2;
	if (!ft_strncmp(string, "sp", len))
		parse_sphere(split_line, data, obj_index);
	if (!ft_strncmp(string, "pl", len))
		parse_plane(split_line, data, obj_index);
	if (!ft_strncmp(string, "cy", len))
		parse_cylinder(split_line, data, obj_index);
}

int	line_check(char ***split_line)
{
	int	j;
	int	k;
	int	count;

	count = 0;
	j = 0;
	while (split_line[j])
	{
		k = 0;
		while (split_line[j][k])
		{
			count++;
			k++;
		}
		j++;
	}
	return (count);
}

bool	line_check_object(char *line)
{
	if ((line[0] && line[1]) && (!ft_strncmp(line, "sp", 2) || \
	!ft_strncmp(line, "pl", 2) || !ft_strncmp(line, "cy", 2)))
		return (true);
	return (false);
}

bool	line_check_data(char *line)
{
	if (line[0] && (line[0] == 'A' || line[0] == 'C' || line[0] == 'L'))
		return (true);
	if (line[0] && (line[0] == 'a' || line[0] == 'c' || line[0] == 'l'))
		return (true);
	return (false);
}
