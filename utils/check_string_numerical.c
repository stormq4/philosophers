/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_string_numerical.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: stormdequay <stormdequay@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 11:07:17 by stormdequay   #+#    #+#                 */
/*   Updated: 2022/02/25 11:16:16 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

int	check_string_numerical(const char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (FALSE);
		str++;
	}
	return (TRUE);
}
