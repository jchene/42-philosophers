/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:54:57 by jchene            #+#    #+#             */
/*   Updated: 2022/04/14 15:30:08 by jchene           ###   ########.fr       */
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
