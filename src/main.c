/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/09 18:01:43 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int main(int argc, char **argv)
{
	mlx_t* mlx;
	(void)argc;
	(void)argv;

	mlx = mlx_init(1600, 800, "MiniRT", true);
	mlx_loop(mlx);
	return 0;
}