/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:29:57 by jchene            #+#    #+#             */
/*   Updated: 2022/04/14 15:30:56 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	get_first_fork(t_philo *philo)
{	
	if ((philo->id % 2))
		prt_fork(philo, pthread_mutex_lock(&(philo->left_fork)) + LEFT);
	else
		prt_fork(philo, pthread_mutex_lock(philo->right_fork) + RIGHT);
}

void	get_last_fork(t_philo *philo)
{	
	if ((philo->id % 2))
		prt_fork(philo, pthread_mutex_lock(philo->right_fork) + RIGHT);
	else
		prt_fork(philo, pthread_mutex_lock(&(philo->left_fork)) + LEFT);
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