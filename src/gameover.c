/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameover.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 11:07:02 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/04/14 16:12:57 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	game_check(t_philo *philo, t_rules *rules, size_t i)
{
	pthread_mutex_lock(&philo[i % rules->philo_nr].is_done);
	if (philo[i % rules->philo_nr].done == FALSE)
	{
		pthread_mutex_unlock(&philo[i % rules->philo_nr].is_done);
		pthread_mutex_lock(&philo[i % rules->philo_nr].cycle);
		if (return_time() - philo[i % rules->philo_nr].cycle_time \
		>= philo->rules->ttd)
		{
			pthread_mutex_unlock(&philo[i % rules->philo_nr].cycle);
			pthread_mutex_lock(&rules->print);
			rules->dead = TRUE;
			pthread_mutex_unlock(&rules->print);
			return (FALSE);
		}
		pthread_mutex_unlock(&philo[i % rules->philo_nr].cycle);
	}
	else
	{
		pthread_mutex_unlock(&philo[i % rules->philo_nr].is_done);
		return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief checks if the cycle time exceeds time to die for every philo
 * or if the simulation is done
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
		if (!game_check(philo, rules, i))
			break ;
		usleep(500);
		i++;
	}
	rules->dead_philo_id = i % rules->philo_nr + 1;
}
