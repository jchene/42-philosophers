/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:54:57 by jchene            #+#    #+#             */
/*   Updated: 2022/04/08 15:52:10 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	try_lock(pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	pthread_mutex_unlock(lock);
}

void	get_eat_time(t_philo *philo)
{
	pthread_mutex_lock(&(philo->eat_lock));
	gettimeofday(philo->last_eat, NULL);
	pthread_mutex_unlock(&(philo->eat_lock));
}

void	get_forks(t_philo *philo)
{
	if (philo->philo_id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("[%u] philo %d has taken a fork\n",
			get_ms_dif(philo->data_cpy.start_time), philo->philo_id);
		pthread_mutex_lock(philo->right_fork);
		printf("[%u] philo %d has taken a fork\n",
			get_ms_dif(philo->data_cpy.start_time), philo->philo_id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("[%u] philo %d has taken a fork\n",
			get_ms_dif(philo->data_cpy.start_time), philo->philo_id);
		pthread_mutex_lock(philo->left_fork);
		printf("[%u] philo %d has taken a fork\n",
			get_ms_dif(philo->data_cpy.start_time), philo->philo_id);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->philo_id % 2)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}
