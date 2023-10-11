/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 10:19:24 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/10 13:50:03 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//0x  FF FF FF
//Hex RR GG BB

uint32_t get_rgba(double r, double g, double b, double a)
{
    char    *hex;

    (void)a;
    (void)g;
    (void)b;
    (void)r;
    hex = "0xFFFFFFFF";
    return (*(uint32_t*)hex);
}
