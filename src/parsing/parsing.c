/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 12:06:04 by svan-has      #+#    #+#                 */
/*   Updated: 2023/10/25 14:18:03 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"
#include <fcntl.h> 

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_split_array(char **split_file, char ***split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
	{
		free_split(split_line[i]);
		i++;
	}
	free(split_line);
	free_split(split_file);
}

void	process_split_line(char **split_file, t_data *data, int obj_index)
{
	int		i;
	char	***split_line;

	(void)data;
	split_line = NULL;
	i = 0;
	while (split_file[i])
		i++;
	split_line = null_check(malloc (i * sizeof(char **)));
	if (line_check_object(split_file[0]) || line_check_data(split_file[0]))
	{
		i = 0;
		while (split_file[++i])
			split_line[i - 1] = null_check(ft_split(split_file[i], ','));
		split_line[i - 1] = NULL;
	}
	check_object_data(split_file[0], split_line, data, obj_index);
	free_split_array(split_file, split_line);
}

char	**process_file(char *file, t_data *data)
{
	int		rt_file;
	int		obj_index;
	char	*line;
	char	**split_line;

	split_line = NULL;
	obj_index = 0;
	rt_file = open (file, O_RDONLY);
	if (rt_file < 0)
		error_exit("Cannot open file");
	while (1)
	{
		line = get_next_line(rt_file);
		if (!line)
			break ;
		if (line_check_data(line) || line_check_object(line))
		{
			replace_char(&line, '\t', ' ');
			line = null_check(ft_strtrim_free(line, "\n"));
			split_line = null_check(ft_split(line, ' '));
			process_split_line(split_line, data, obj_index);
			if (line_check_object(line))
				obj_index++;
		}
		free(line);
	}
	close (rt_file);
	return (split_line);
}

void	parse_input(int argc, char **argv, char ***split_file, t_data *data)
{
	error_check(argc, argv);
	count_objects(argv[1], data);
	*split_file = process_file(argv[1], data);
}
