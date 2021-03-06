/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/07 13:59:33 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/04/14 16:02:46 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief prints the message of the action of the philo with a mutex
 * 
 * @param str message
 * @param p_mutex mutex for printinf
 * @param b_time begin time
 * @param id of the philo
 */
int	print_action(char *str, t_philo *philo, t_fork *fork, t_fork *n_fork)
{
	pthread_mutex_lock(&philo->rules->print);
	if (philo->rules->dead == TRUE)
	{
		pthread_mutex_unlock(&philo->rules->print);
		if (fork)
			pthread_mutex_unlock(&fork->fork);
		if (n_fork)
			pthread_mutex_unlock(&n_fork->fork);
		return (error);
	}
	printf("%lu %zu %s\n", return_time() - philo->rules->b_time, \
	philo->philo_id, str);
	pthread_mutex_unlock(&philo->rules->print);
	return (succes);
}

/**
 * @brief checks which philosopher died and prints it with time stamp
 * 
 * @param rules 
 */
void	print_dead(t_rules *rules)
{
	usleep(1000);
	pthread_mutex_lock(&rules->print);
	if (rules->dead_philo_id && rules->dead == TRUE)
	{
		printf("%lu %zu %s\n", return_time() - rules->b_time, \
		rules->dead_philo_id, "died");
		pthread_mutex_unlock(&rules->print);
	}
	pthread_mutex_unlock(&rules->print);
}
