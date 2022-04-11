/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:54:57 by jchene            #+#    #+#             */
/*   Updated: 2022/04/11 19:39:28 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	try_lock(pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	pthread_mutex_unlock(lock);
}

void	get_fork(t_philo *philo, unsigned int fork)
{	
	if ((philo->id % 2))
	{
		if (fork == FIRST)
			pthread_mutex_lock(&(philo->left_fork));
		else
			pthread_mutex_lock(philo->right_fork);
		print_state(philo, FORK);
	}
	else
	{
		if (fork == FIRST)
			pthread_mutex_lock(philo->right_fork);
		else
			pthread_mutex_lock(&(philo->left_fork));
		print_state(philo, FORK);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&(philo->left_fork));
	}
	else
	{
		pthread_mutex_unlock(&(philo->left_fork));
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	set_eat_time(t_philo *philo)
{
	pthread_mutex_lock(&(philo->eat_lock));
	gettimeofday(&(philo->last_eat), NULL);
	pthread_mutex_unlock(&(philo->eat_lock));
}

void	switch_locks(t_philo *philo, unsigned int state)
{
	if (stats == ON)
	{
		pthread_mutex_lock(&(philo->live_lock));
		pthread_mutex_lock();
	}
}
