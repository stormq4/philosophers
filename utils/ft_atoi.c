/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: stormdequay <stormdequay@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 17:28:20 by stormdequay   #+#    #+#                 */
/*   Updated: 2022/02/25 11:16:29 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_power(int ground, int power)
{
	long long	value;

	value = 1;
	if (power < 0)
		return (0);
	else if (power == 0)
		return (value);
	while (power)
	{
		value *= ground;
		power--;
	}
	return (value);
}

int	ft_atoi_calc(const char *str, int len)
{
	int			i;
	long long	atoi;

	i = 0;
	atoi = 0;
	while (len)
	{
		atoi += ((str[len - 1] - '0') * ft_power(10, i));
		i++;
		len--;
	}
	return (atoi);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;

	neg = 1;
	while (*str == '\t' || *str == '\n' || \
	*str == '\v' || *str == '\f' || \
	*str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		i++;
	}
	return (ft_atoi_calc(str, i) * neg);
}
