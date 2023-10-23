/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 14:57:54 by svan-has      #+#    #+#                 */
/*   Updated: 2023/10/23 16:38:52 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"

char    *input_check(char *string)
{
    int     i;
    bool    dot;
    
    i = 0;
    dot = false;
    while (string[i])
    {
        if (ft_isdigit(string[i]))
            i++;
        else if (!dot && string[i] == '.')
        {
            i++;
            dot = true;
        }
        else
            error_exit();
    }
    return (string);
}