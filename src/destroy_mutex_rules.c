/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy_mutex_rules.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: stormdequay <stormdequay@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 15:38:32 by stormdequay   #+#    #+#                 */
/*   Updated: 2022/04/14 11:20:56 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex_rules(t_rules *rules)
{
	pthread_mutex_destroy(&rules->print);
}
