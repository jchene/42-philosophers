/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:40:10 by jchene            #+#    #+#             */
/*   Updated: 2022/04/09 21:19:13 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned int	get_ms_dif(struct timeval s_time)
{
	time_t			sec;
	suseconds_t		usec;
	unsigned int	ms_dif;
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	sec = timestamp.tv_sec - s_time.tv_sec;
	usec = 1000000 - s_time.tv_usec + timestamp.tv_usec;
	ms_dif = ((unsigned int)sec * 1000) + ((unsigned int)usec / 1000);
	return (ms_dif);
}

int	msleep(unsigned int wait, t_philo *philo)
{
	struct timeval	timestamp;
	struct timeval	end;
	unsigned int	ms;

	ms = wait;
	gettimeofday(&timestamp, NULL);
	end.tv_sec = timestamp.tv_sec + (ms / 1000);
	ms = ms % 1000;
	end.tv_usec = timestamp.tv_usec + (ms * 1000);
	end.tv_sec = end.tv_sec + (end.tv_usec / 1000000);
	end.tv_usec = end.tv_usec % 1000000;
	while ((timestamp.tv_sec < end.tv_sec)
		|| (timestamp.tv_sec == end.tv_sec && timestamp.tv_usec < end.tv_usec))
	{
		gettimeofday(&timestamp, NULL);
		usleep(10);
		pthread_mutex_lock(&(philo->live_lock));
		if (philo->live != 1)
			return (pthread_mutex_unlock(&(philo->live_lock)) - 1);
	}
	return (0);
}