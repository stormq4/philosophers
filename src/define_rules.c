/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   define_rules.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: stormdequay <stormdequay@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 11:00:07 by stormdequay   #+#    #+#                 */
/*   Updated: 2022/04/12 15:06:55 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief initializes mutex rules
 * 
 * @param rules 
 * @return int for erroor or succes
 */
static int	initialize_mutex_rules(t_rules *rules)
{
	rules->dead = FALSE;
	rules->dead_philo_id = 0;
	rules->philos_done = 0;
	rules->b_time = return_time();
	if (pthread_mutex_init(&rules->print, NULL) != thread_succes)
		return (error);
	if (pthread_mutex_init(&rules->philo_done, NULL) != thread_succes)
		return (error);
	return (succes);
}

/**
 * @brief reads the input from the command line and puts it in the given
 * attribute of the rules struct.
 * 
 * @param rules is the struct for rules
 * @param argc argument count
 * @param argv arguments passed in 2d char array
 * @return int is a Boolean upon completion of the 
 */
int	define_rules(t_rules *rules, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!check_string_numerical(argv[i]))
			return (error);
		i++;
	}
	rules->philo_nr = (size_t)ft_atoi(argv[1]);
	if (rules->philo_nr == 0)
		return (errno);
	rules->ttd = (size_t)ft_atoi(argv[2]);
	rules->tte = (size_t)ft_atoi(argv[3]);
	rules->tts = (size_t)ft_atoi(argv[4]);
	if (argc == 6)
		rules->nr_must_eat = (size_t)ft_atoi(argv[5]);
	else
		rules->nr_must_eat = (size_t)FALSE;
	if (initialize_mutex_rules(rules) == error)
		return (error);
	return (succes);
}
