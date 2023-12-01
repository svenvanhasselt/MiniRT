/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 16:47:30 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/29 14:02:21 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

/* Infinite cylinder equation :
x2 + z2 - r2 = 0;
q is a point on the cylinder
pa + vat is the middle line of cylinder
(q - pa -(va, q-pa) va)2 - r2 = 0;

To find intersection points with a ray p +vt
(p - p + vt - (va,p = pa + vt)va)2 - r2 = 0;
At2 + Bt2 + C = 0
A = (v - ())

 */
bool	hit_cylinder(t_object *obj, t_ray *ray)
{
	float   a;
    float   b;
    float   c;
    float   t;

    a = ray->dir.x * ray->dir.x + ray->dir.y * ray->dir.y;
    b = 2 * (ray->dir.x * ray->orig.x + ray->dir.y * ray->orig.y);
    c = ray->orig.x * ray->orig.x + ray->orig.y * ray->orig.y - obj->cyl_diameter;
    t = b*b - 4*a*c;
    obj->t = (-b/2 -sqrt(t)) / a;
    if (obj->t < 0)
        return (false);
    return (true);
}