/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_philos.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/04 15:01:54 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/04/12 14:22:42 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_philos(t_philo **philos)
{
	free(*philos);
	return (error);
}

/**
 * @brief frees the forks and destorys the mutexes in the forks
 * 
 * @param philo 
 * @param f_fail 
 * @return int 
 */
int	free_forks(t_philo **philo, int f_fail)
{
	int		i;
	t_philo	*phil;

	phil = *philo;
	i = 0;
	while (i < f_fail)
	{
		if ((size_t)f_fail != phil[i].rules->philo_nr && i == f_fail - 1)
			break ;
		pthread_mutex_destroy(&phil[i].fork->fork);
		pthread_mutex_destroy(&phil[i].cycle);
		free(phil[i].fork);
		i++;
	}
	return (free_philos(philo));
}

/**
 * @brief threads are joined function free_forks is called. If a thread fails
 * the firs thread untill the previous one is freed. 
 * 
 * @param philo 
 * @param t_fail 
 * @return int for succes or error
 */
int	join_threads(t_philo **philo, int t_fail)
{
	int		i;
	t_philo	*phil;

	phil = *philo;
	i = 0;
	while (i < t_fail && t_fail > 0)
	{
		pthread_join(phil[i].thread_id, NULL);
		i++;
	}
	return (free_forks(philo, (*philo)->rules->philo_nr));
}
