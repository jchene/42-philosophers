/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:40:10 by jchene            #+#    #+#             */
/*   Updated: 2022/04/15 14:44:15 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned int	get_tempo(struct timeval s_time)
{
	struct timeval	stamp;

	gettimeofday(&stamp, NULL);
	if (s_time.tv_sec > stamp.tv_sec)
		return (FUTURE);
	else if (s_time.tv_sec == stamp.tv_sec && s_time.tv_usec > stamp.tv_usec)
		return (FUTURE);
	else
		return (PAST);
}

unsigned int	get_ms_dif(struct timeval s_time)
{
	struct timeval	*future;
	struct timeval	*past;
	struct timeval	stamp;
	unsigned int	dif;

	gettimeofday(&stamp, NULL);
	if (get_tempo(s_time) == FUTURE)
	{
		future = &s_time;
		past = &stamp;
	}
	else
	{
		future = &stamp;
		past = &s_time;
	}
	dif = future->tv_sec - past->tv_sec;
	dif = dif * 1000000;
	dif = (dif - past->tv_usec) + future->tv_usec;
	return (dif / 1000);
}

int	mcheck_sleep(unsigned int wait, t_philo *philo)
{
	struct timeval	stamp;
	struct timeval	end;

	gettimeofday(&stamp, NULL);
	end.tv_sec = stamp.tv_sec + (wait / 1000);
	end.tv_usec = stamp.tv_usec + ((wait % 1000) * 1000);
	end.tv_sec = end.tv_sec + (end.tv_usec / 1000000);
	end.tv_usec = end.tv_usec % 1000000;
	while (get_tempo(end) == FUTURE)
	{
		usleep(42);
		if (!check_life(philo) || !check_others(philo))
			return (0);
	}
	return (1);
}
