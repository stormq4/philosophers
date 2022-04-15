/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: stormdequay <stormdequay@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 14:15:36 by stormdequay   #+#    #+#                 */
/*   Updated: 2022/04/14 11:53:10 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

# include "philo_utils.h"

/**
 * @brief fork struct 
 * 
 * @param fork mutex for each fork
 */
typedef struct s_fork {
	pthread_mutex_t	fork;
}			t_fork;

/**
 * @brief rules of the simulation
 * 
 * @param ttd time_to_die: each philosopher must eat within this time window
 * @param tte time_to_eat: eating time of each philosopher
 * @param tts time_to_sleep: time philosopher spends sleeping
 * @param nr_must_eat number_of_times_each_philosopher_must_eat
 * @param philo_nr nr of philosophers in simulation
 * @param print mutex for printing
 * @param gameover mutex to check if the game is over
 * @param dead boolean changed with mutex
 * @param dead_philo_id
 * @param philo_done mutex for eaten philos
 * @param philos_done nr of philos done eating
 */
typedef struct s_rules {
	size_t			ttd;
	size_t			tte;
	size_t			tts;
	size_t			nr_must_eat;
	size_t			philo_nr;
	pthread_mutex_t	print;
	t_bool			dead;
	size_t			dead_philo_id;
	unsigned long	b_time;
}				t_rules;

/**
 * @brief struct for each philosopher
 * 
 * @param philo_id
 * @param fork 
 * @param n_fork neigbour fork
 * @param thread_id
 * @param cycle mutex for assigning cyle time
 * @param cycle_time beginning time of each cycle
 */
typedef struct s_philo{
	size_t			philo_id;
	t_fork			*fork;
	t_fork			*n_fork;
	pthread_t		thread_id;
	pthread_mutex_t	cycle;
	pthread_mutex_t	is_done;
	unsigned long	cycle_time;
	t_bool			done;
	t_rules			*rules;
}				t_philo;

//			define_rules.c
int				define_rules(t_rules *rules, int argc, char **argv);

//			make_philosophers.c
int				make_philosophers(t_rules *rules, t_philo **philo);

//			simulation.c
void			*philo_start(void *arr);

// 			free_philos.c
int				free_philos(t_philo **philos);
int				free_forks(t_philo **philo, int f_fail);
int				join_threads(t_philo **philo, int t_fail);

//			print_action.c
int				print_action(char *str, t_philo *philo, t_fork *fork, \
t_fork *n_fork);
void			print_dead(t_rules *rules);

//			gameover.c
void			check_game_over(t_philo **philos, t_rules *rules);

//			destroy_mutex_rules.c
void			destroy_mutex_rules(t_rules *rules);

//			sleep_time.c
unsigned long	return_time(void);
void			smart_sleep(int m_sec);

#endif
