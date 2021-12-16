/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_skip.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 11:39:30 by dnoom         #+#    #+#                 */
/*   Updated: 2021/12/16 11:39:36 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_skip(char **s, char c)
{
	int	i;

	i = 0;
	while ((*s)[i] == c)
		i++;
	(*s) += i;
	return (i);
}
