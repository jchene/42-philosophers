/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:14:03 by jchene            #+#    #+#             */
/*   Updated: 2022/03/31 19:36:52 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	unsigned int	nb_philo;
	unsigned int	death_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	unsigned int	max_eat;
	pthread_t		**threads;
}				t_philo;

#endif