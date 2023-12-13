/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 09:10:52 by yizhang       #+#    #+#                 */
/*   Updated: 2023/12/13 14:10:24 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

// This function is to compare which t is closer to the camera
float	compare_t(float t, float t2)
{
	if (t < 0 && t2 >= 0)
		return (t2);
	else if (t2 < 0 && t >= 0)
		return (t);
	else if (t >= 0 && t2 >= 0)
	{
		if (t < t2)
			return (t);
		else
			return (t2); 
	}
	return (-1);
}
