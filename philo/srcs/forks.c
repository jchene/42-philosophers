/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:29:57 by jchene            #+#    #+#             */
/*   Updated: 2022/04/23 18:13:48 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	get_first_fork(t_philo *philo)
{	
	if ((philo->id % 2))
		pthread_mutex_lock(&(philo->left_fork));
	else
		pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
}

void	get_last_fork(t_philo *philo)
{	
	if ((philo->id % 2))
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(&(philo->left_fork));
	print_state(philo, "has taken a fork");
}

void	drop_first_fork(t_philo *philo)
{	
	if ((philo->id % 2))
		pthread_mutex_unlock(&(philo->left_fork));
	else
		pthread_mutex_unlock(philo->right_fork);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->left_fork));
	pthread_mutex_unlock(philo->right_fork);
}

int	check_fork_drop(t_philo *philo, unsigned int forks)
{
	if (!philo->live || !philo->all_alive)
	{
		if (forks == 1)
			drop_first_fork(philo);
		else if (forks == 2)
			drop_forks(philo);
		return (-1);
	}
	else if (&(philo->left_fork) == philo->right_fork)
	{
		philo->live = 0;
		drop_first_fork(philo);
		return (-1);
	}
	return (0);
}
