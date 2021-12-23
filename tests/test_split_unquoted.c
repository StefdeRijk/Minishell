/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_shell_split.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 14:34:40 by dnoom         #+#    #+#                 */
/*   Updated: 2021/12/23 13:43:31 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"
#include "../Libft/libft.h"
#include "stdlib.h"

void	print_free(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		printf("%d: %s\n", i, result[i]);
		i++;
	}
	printf("\n");
	ft_free_strs(result);
}

int	main(void)
{
	char		*string;
	static int	wq1[] = {0, 0, 0, 0, 0};
	static int	wq2[] = {0, 0, 0, 1, 0};

	string = "hallo";
	print_free(ft_split_unquoted(string, 'a', wq1));
	print_free(ft_split_unquoted(string, 'l', wq1));
	print_free(ft_split_unquoted(string, 'l', wq2));
}
