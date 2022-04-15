/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:54:57 by jchene            #+#    #+#             */
/*   Updated: 2022/04/15 14:30:17 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	try_lock(pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	pthread_mutex_unlock(lock);
}

void	kill_all(t_reaper *reaper)
{
	unsigned int	j;

	j = 0;
	while (j < reaper->nb_philo)
	{
		pthread_mutex_lock(&(reaper->philos[j]->live_lock));
		reaper->philos[j]->all_alive = 0;
		pthread_mutex_unlock(&(reaper->philos[j]->live_lock));
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

void	print_state(t_philo *philo, const char *str)
{
	pthread_mutex_lock(philo->print_lock);
	printf("[%u] philo %u %s\n", get_ms_dif(philo->start_time), philo->id, str);
	pthread_mutex_unlock(philo->print_lock);
}
