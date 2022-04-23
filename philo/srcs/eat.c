/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:48:26 by jchene            #+#    #+#             */
/*   Updated: 2022/04/23 14:50:19 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->eat_lock));
	gettimeofday(&(philo->last_eat), NULL);
	pthread_mutex_unlock(&(philo->eat_lock));
}

unsigned int	check_all_done(t_reaper *rp)
{
	unsigned int	i;

	if (rp->max_meal < 0)
		return (0);
	i = 0;
	while (i < rp->nb_philo)
	{
		if (rp->philos[i]->nb_meal < rp->max_meal)
			return (0);
		i++;
	}
	return (1);
}
