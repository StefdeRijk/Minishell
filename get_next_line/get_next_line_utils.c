/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 11:50:25 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 11:50:26 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (dst);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

void	*ft_realloc(void *p, size_t size, size_t old_size)
{
	void	*new;

	new = malloc(size);
	if (new)
		ft_memcpy(new, p, old_size);
	free(p);
	return (new);
}
