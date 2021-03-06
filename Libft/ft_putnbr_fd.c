/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:23:44 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:23:46 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	char	c;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr *= -1;
	}
	if (nbr < 10)
	{
		c = (nbr % 10) + '0';
		ft_putchar_fd(c, fd);
	}
	else
	{
		ft_putnbr_fd(nbr / 10, fd);
		c = (nbr % 10) + '0';
		ft_putchar_fd(c, fd);
	}
}
