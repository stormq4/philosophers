/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep_time.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/12 15:22:39 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/04/14 16:12:23 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	return_time(void)
{
	struct timeval	t;
	unsigned long	time;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

/**
 * @brief usleep has too much interference
 * 
 * @param m_sec milliseconds to sleep
 */
void	smart_sleep(int m_sec)
{
	unsigned long	start;

	start = return_time();
	while ((int)(return_time() - start) < m_sec)
		usleep(500);
}
