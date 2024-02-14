/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 13:51:44 by svan-has      #+#    #+#                 */
/*   Updated: 2024/01/26 14:18:46 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"
#include <fcntl.h>

char	*input_check(char *string)
{
	int		i;
	bool	dot;

	i = 0;
	dot = false;
	while (string[i])
	{
		if (ft_isdigit(string[i]) || string[i] == '-')
			i++;
		else if (!dot && string[i] == '.')
		{
			i++;
			dot = true;
		}
		else
			error_exit("Wrong formatting of data");
	}
	return (string);
}

void	error_check(int argc, char **argv, int *rt_file)
{
	int	len;

	if (argc != 2)
		error_exit("Needs an .rt file as input");
	len = ft_strlen(argv[1]);
	if (len < 4)
		error_exit("Needs an .rt file as input");
	if (ft_strncmp(argv[1] + (len - 3), ".rt", 3))
		error_exit("Needs an .rt file as input");
	*rt_file = open (argv[1], O_RDONLY);
	if (*rt_file < 0)
		error_exit("Cannot open file");
}
