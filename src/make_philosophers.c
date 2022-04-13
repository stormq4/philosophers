/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_philosophers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: stormdequay <stormdequay@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 14:05:59 by stormdequay   #+#    #+#                 */
/*   Updated: 2022/04/12 10:21:44 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	initialize_fork_mutex(t_fork *fork)
{
	if (pthread_mutex_init(&fork->fork, NULL) != thread_succes)
		return (error);
	return (succes);
}

/**
 * @brief assigns forks of the philosophers to its neighbour
 * 
 * @param philo 
 * @param rules 
 */
static void	assign_fork_pair(t_philo **philo, t_rules *rules)
{
	size_t	i;
	t_philo	*phil;

	phil = *philo;
	i = 0;
	while (i < rules->philo_nr - 1)
	{
		phil[i].n_fork = phil[i + 1].fork;
		i++;
	}
	phil[i].n_fork = phil[0].fork;
}

/**
 * @brief mallocs and initilizes the mutexes in the forks 
 * 
 * @param rules 
 * @param philo 
 * @return int for error or succes
 */
static int	malloc_fork(t_rules *rules, t_philo **philo)
{
	size_t	i;
	t_philo	*phil;

	phil = *philo;
	i = 0;
	while (i < rules->philo_nr)
	{
		phil[i].fork = malloc(sizeof(t_fork));
		if (!phil[i].fork)
			return (free_forks(philo, i));
		if (initialize_fork_mutex(phil[i].fork) == error)
			return (free_forks(philo, i + 1));
		i++;
	}
	assign_fork_pair(philo, rules);
	return (succes);
}

/**
 * @brief makes and initializes the philos with the corresponding threads
 * creates thread ->> check simulation.c
 * 
 * @param rules rules of the simulation
 * @param philo malloced philos
 * @return int return succes or error
 */
int	make_philosophers(t_rules *rules, t_philo **philo)
{
	size_t	i;
	t_philo	*phil;

	phil = *philo;
	i = 0;
	while (i < rules->philo_nr)
	{
		phil[i].philo_id = i + 1;
		phil[i].rules = rules;
		phil[i].cycle_time = rules->b_time;
		pthread_mutex_init(&phil[i].cycle, NULL);
		i++;
	}
	if (malloc_fork(rules, philo) == error)
		return (error);
	i = 0;
	while (i < rules->philo_nr)
	{
		if (pthread_create(&phil[i].thread_id, NULL, philo_start, &phil[i]))
			return (join_threads(philo, (int)i));
		i++;
	}
	return (succes);
}
