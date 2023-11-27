/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 10:19:24 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/27 17:04:12 by svan-has      ########   odam.nl         */
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
   r = clamp(r, 0.0, 1.0) *  255;
   g = clamp(g, 0.0, 1.0) * 255;
   b = clamp(b, 0.0, 1.0) * 255;
   return ((int)r << 24 | (int)g << 16 | (int)b << 8 | (int)a);
}
