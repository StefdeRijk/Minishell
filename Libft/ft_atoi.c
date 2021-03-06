/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:26:17 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:26:17 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int		n;
	long	i;

	i = 0;
	n = 1;
	while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\n'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-')
	{
		n = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		i *= 10;
		i += *str - '0';
		str++;
	}
	i *= n;
	return ((int)i);
}
