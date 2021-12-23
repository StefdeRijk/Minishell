/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_shell_split.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 14:34:40 by dnoom         #+#    #+#                 */
/*   Updated: 2021/12/23 13:45:22 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"
#include "../Libft/libft.h"
#include "stdlib.h"

void	print_parts(t_part *parts)
{
	int		i;

	i = 0;
	while (parts[i].part)
	{
		printf("-%s- type: %d\n", parts[i].part, parts[i].type);
		i++;
	}
	printf("\n");
}

int	main(void)
{
	int				i;
	static t_part	parts1s[] = {{"bla asf", NORMAL},
	{"een twee drie vier vijf", NORMAL},
	{"blie bloe", NORMAL},
	{NULL, NORMAL}};
	t_part			*parts1;

	parts1 = ft_memdup(parts1s, sizeof(parts1s));
	i = 0;
	while (parts1[i].part)
	{
		parts1[i].part = ft_strdup(parts1[i].part);
		i++;
	}
	replace_parts(&parts1, 1);
	print_parts(parts1);
	replace_parts(&parts1, 6);
	print_parts(parts1);
	ft_free_parts(parts1);
}
