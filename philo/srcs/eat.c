/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:48:26 by jchene            #+#    #+#             */
/*   Updated: 2022/04/15 23:35:04 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->eat_lock));
	gettimeofday(&(philo->last_eat), NULL);
	pthread_mutex_unlock(&(philo->eat_lock));
}

unsigned int	get_nb_meal(t_philo *philo)
{
	pthread_mutex_lock(&(philo->eat_lock));
	return (philo->nb_meal + pthread_mutex_unlock(&(philo->eat_lock)));
}

unsigned int	check_done(t_reaper *reaper)
{
	if (reaper->done_eating >= reaper->nb_philo)
	{
		kill_all(reaper);
		return (1);
	}
	return (0);
}
