/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 10:19:24 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/29 15:31:20 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//0x  FF FF FF
//Hex RR GG BB
//converts a color to a uint32_t RGBA(MLX)

float clamp(float value, float min, float max)
{
   if (value < min)
      value = 0.0;
   if (value > max)
      value = 1.0;
   return (value);
}

uint32_t get_rgba(float r, float g, float b, float a)
{
   return ((uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | (uint32_t)a);
}
