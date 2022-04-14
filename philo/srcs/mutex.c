/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:54:57 by jchene            #+#    #+#             */
/*   Updated: 2022/04/14 17:07:40 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	try_lock(pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	pthread_mutex_unlock(lock);
}

void	set_eat_time(t_philo *philo)
{
	pthread_mutex_lock(&(philo->eat_lock));
	gettimeofday(&(philo->last_eat), NULL);
	pthread_mutex_unlock(&(philo->eat_lock));
}

void	set_var(pthread_mutex_t *lock, unsigned int *var, unsigned int value)
{
	pthread_mutex_lock(lock);
	*var = value;
	pthread_mutex_unlock(lock);
}

void	kill_all(t_reaper *reaper)
{
	unsigned int	j;

	j = 0;
	while (j < reaper->nb_philo)
	{
		set_var(&(reaper->philos[j]->live_lock),
			&(reaper->philos[j]->live), 0);
		j++;
	}
}

void	join_all(t_reaper *reaper)
{
	unsigned int	i;

	i = 0;
	while (i < reaper->nb_philo)
	{
		pthread_join(reaper->philos[i]->thread, NULL);
		i++;
	}
}
