/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:54:57 by jchene            #+#    #+#             */
/*   Updated: 2022/04/23 12:19:29 by jchene           ###   ########.fr       */
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
		reaper->philos[j++]->all_alive = 0;
}

void	execute(t_reaper *reaper)
{
	reaper->philos[reaper->loc_id]->live = 0;
	reaper->dead_id = reaper->philos[reaper->loc_id]->id;
	kill_all(reaper);
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
