/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 17:47:22 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/17 17:50:22 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	render(mlx_image_t *img)
{
	for(int j = 0; j < 1600; j++)
	{
		for(int i = 0; i < 800; i++)
		{
			if (hit_object())
				mlx_put_pixel(img, j, i, 0xFFFFFFFF);//print white
			else
				mlx_put_pixel(img, j, i, 0xFFFFFFFF);//other color
		}
			
	}
}

hit_object()