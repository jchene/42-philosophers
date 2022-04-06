/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:54:57 by jchene            #+#    #+#             */
/*   Updated: 2022/04/06 18:15:23 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	get_forks(t_philo *philo)
{
	if (philo->philo_id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("[] philo %d has taken a fork\n", philo->philo_id);
		pthread_mutex_lock(philo->right_fork);
		printf("[] philo %d has taken a fork\n", philo->philo_id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("[] philo %d has taken a fork\n", philo->philo_id);
		pthread_mutex_lock(philo->left_fork);
		printf("[] philo %d has taken a fork\n", philo->philo_id);
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
