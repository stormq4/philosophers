/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: stormdequay <stormdequay@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 14:15:25 by stormdequay   #+#    #+#                 */
/*   Updated: 2022/04/11 14:55:26 by stormdequay   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_UTILS_H
# define PHILO_UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

/**
 * @brief enum foor boeleans
 */
typedef enum e_bool {
	TRUE = 1,
	FALSE = 0
}				t_bool;

/**
 * @brief enum for succes and error codes for return values
 */
typedef enum e_error {
	succes_main = 0,
	error_main = 1,
	thread_succes = 0,
	error = 0,
	succes = 1
}				t_error;

int	ft_atoi(const char *str);
int	check_string_numerical(const char *str);

#endif
