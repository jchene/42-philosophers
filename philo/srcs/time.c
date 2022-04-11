/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:40:10 by jchene            #+#    #+#             */
/*   Updated: 2022/04/11 19:19:30 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned int	get_us_dif(struct timeval s_time)
{
	struct timeval	*future;
	struct timeval	*past;
	unsigned int	dif;
	struct timeval	stamp;

	gettimeofday(&stamp, NULL);
	if (s_time.tv_sec > stamp.tv_sec)
		future = &s_time;
	else if (s_time.tv_sec == stamp.tv_sec && s_time.tv_usec > stamp.tv_usec)
		future = &s_time;
	else
		future = &stamp;
	if (future == &s_time)
		past = &stamp;
	else
		past = &s_time;
	dif = future->tv_sec - past->tv_sec;
	dif = dif * 1000000;
	dif = (dif - past->tv_usec) + future->tv_usec;
	return (dif);
}

unsigned int	get_ms_dif(struct timeval s_time)
{
	struct timeval	*future;
	struct timeval	*past;
	unsigned int	dif;
	struct timeval	stamp;

	gettimeofday(&stamp, NULL);
	if (s_time.tv_sec > stamp.tv_sec)
		future = &s_time;
	else if (s_time.tv_sec == stamp.tv_sec && s_time.tv_usec > stamp.tv_usec)
		future = &s_time;
	else
		future = &stamp;
	if (future == &s_time)
		past = &stamp;
	else
		past = &s_time;
	dif = future->tv_sec - past->tv_sec;
	dif = dif * 1000000;
	dif = (dif - past->tv_usec) + future->tv_usec;
	return ((dif / 1000));
}

int	msleep(unsigned int wait, t_philo *philo, unsigned int type)
{
	struct timeval	stamp;
	struct timeval	end;

	gettimeofday(&stamp, NULL);
	end.tv_sec = stamp.tv_sec + (wait / 1000);
	end.tv_usec = stamp.tv_usec + ((wait % 1000) * 1000);
	end.tv_sec = end.tv_sec + (end.tv_usec / 1000000);
	end.tv_usec = end.tv_usec % 1000000;
	while (get_ms_dif(end) > 0)
	{
		usleep(50);
		pthread_mutex_lock(&(philo->live_lock));
		if (philo->live != 1)
		{
			pthread_mutex_unlock(&(philo->live_lock));
			if (type == EAT)
				drop_forks(philo);
			return (-1);
		}
		pthread_mutex_unlock(&(philo->live_lock));
	}
	return (0);
}
