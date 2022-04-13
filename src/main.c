/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: stormdequay <stormdequay@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 15:01:30 by stormdequay   #+#    #+#                 */
/*   Updated: 2022/04/13 10:55:42 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (error_main);
	if (define_rules(&rules, argc, argv) == error)
		return (error_main);
	philo = malloc(sizeof(t_philo) * rules.philo_nr);
	if (!philo)
		return (error_main);
	if (make_philosophers(&rules, &philo) == error)
		return (error_main);
	check_game_over(&philo, &rules);
	print_dead(&rules);
	join_threads(&philo, rules.philo_nr);
	destroy_mutex_rules(&rules);
	return (succes_main);
}
