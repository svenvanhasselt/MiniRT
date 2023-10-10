/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/09 18:18:11 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//open window
//give some color
//sending rays into the scene
//vector?
//

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	mlx_t* mlx;

	mlx = mlx_init(1600, 800, "MiniRT", true);
	mlx_loop(mlx);
	return 0;
}