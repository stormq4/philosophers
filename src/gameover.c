/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameover.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 11:07:02 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/04/12 16:00:11 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief checks if the simulation is done
 * 
 * @param rules 
 * @return int 
 */
static int	check_if_done(t_rules *rules)
{
	pthread_mutex_lock(&rules->philo_done);
	if (rules->philos_done == rules->philo_nr)
	{
		pthread_mutex_unlock(&rules->philo_done);
		return (TRUE);
	}
	pthread_mutex_unlock(&rules->philo_done);
	return (FALSE);
}

/**
 * @brief checks if the cycle time exceeds time to die for every philo
 * 
 * @param philos 
 * @param rules 
 */
void	check_game_over(t_philo **philos, t_rules *rules)
{
	size_t	i;
	t_philo	*philo;

	philo = *philos;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo[i % rules->philo_nr].cycle);
		if (return_time() - philo[i % rules->philo_nr].cycle_time \
		>= philo->rules->ttd)
		{
			pthread_mutex_unlock(&philo[i % rules->philo_nr].cycle);
			pthread_mutex_lock(&rules->print);
			rules->dead = TRUE;
			pthread_mutex_unlock(&rules->print);
			break ;
		}
		pthread_mutex_unlock(&philo[i % rules->philo_nr].cycle);
		if (check_if_done(rules))
			return ;
		usleep(500);
		i++;
	}
	rules->dead_philo_id = i % rules->philo_nr + 1;
}
