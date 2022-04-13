/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/06 15:08:24 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/04/13 10:41:33 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief eating implies picking up both forks and then eating. The odd
 * numbered philos wait half of the eating time.
 * 
 * @param b_time 
 * @param philo 
 * @return int succes or error
 */
static int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->n_fork->fork);
	if (print_action("has taken a fork", philo, philo->n_fork, \
	NULL) == error)
		return (error);
	pthread_mutex_lock(&philo->fork->fork);
	if (print_action("has taken a fork", philo, philo->n_fork, \
	philo->fork) == error)
		return (error);
	pthread_mutex_lock(&philo->cycle);
	if (print_action("is eating", philo, philo->n_fork, \
	philo->fork) == error)
	{
		pthread_mutex_unlock(&philo->cycle);
		return (error);
	}
	philo->cycle_time = return_time();
	pthread_mutex_unlock(&philo->cycle);
	smart_sleep((int)philo->rules->tte);
	pthread_mutex_unlock(&philo->n_fork->fork);
	pthread_mutex_unlock(&philo->fork->fork);
	return (succes);
}

/**
 * @brief the cycle time gets locked and is returned. Then eating sleeping 
 * and thinking. Before every print a check for a dead philo is done.
 * 
 * @param b_time begin time of the simulation for the printing
 * @param philo 
 * @param i what round in the simulation
 * @return int for succes or error
 */
int	simulation(t_philo *philo, size_t i)
{
	if (eating(philo) == error)
		return (error);
	if (print_action("is sleeping", philo, NULL, NULL) == error)
		return (error);
	smart_sleep((int)philo->rules->tts);
	if (i < philo->rules->nr_must_eat - 1)
		if (print_action("is thinking", philo, NULL, NULL) == error)
			return (error);
	return (succes);
}

/**
 * @brief starts the simulation of the philosphers. Two different simulations 
 * are used. One for a given nr of must eats and one not.
 * 
 * @param arr philo as void*
 * @return void* 
 */
void	*philo_start(void *arr)
{
	t_philo	*philo;
	size_t	i;

	philo = (t_philo *)arr;
	print_action("is thinking", philo, NULL, NULL);
	usleep(100);
	if (philo->rules->philo_nr == 1)
	{
		print_action("has taken a fork", philo, NULL, NULL);
		return (NULL);
	}
	if (philo->philo_id % 2 == 0)
		usleep(philo->rules->tte * 500);
	if (philo->rules->nr_must_eat)
	{
		i = 0;
		while (i < philo->rules->nr_must_eat)
		{
			if (simulation(philo, i) == FALSE)
				return (NULL) ;
			i++;
		}
		pthread_mutex_lock(&philo->rules->philo_done);
		philo->rules->philos_done++;
		pthread_mutex_unlock(&philo->rules->philo_done);
	}
	else
		while (1)
			if (simulation(philo, 0) == FALSE)
				break ;
	return (NULL);
}
