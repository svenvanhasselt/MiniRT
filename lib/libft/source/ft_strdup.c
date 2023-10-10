/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 16:53:32 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/15 10:17:56 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s1_duplicate;

	s1_duplicate = (char *) malloc (ft_strlen(s1) + 1 * sizeof(char));
	if (s1_duplicate == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s1_duplicate[i] = s1[i];
		i++;
	}
	s1_duplicate[i] = '\0';
	return (s1_duplicate);
}
