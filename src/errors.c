/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 12:09:59 by svan-has      #+#    #+#                 */
/*   Updated: 2023/10/10 16:27:54 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void    error_exit(void)
{
    printf("Error\n");
    exit (1);
}
void    *null_check(void *check)
{
    if (!check)
        error_exit();
    return (check);
}