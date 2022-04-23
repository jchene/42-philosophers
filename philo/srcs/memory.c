/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:16:24 by jchene            #+#    #+#             */
/*   Updated: 2022/04/23 14:47:11 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_calloc(size_t size)
{
	return (memset((malloc(size)), 0, size));
}

void	destroy_mutexes(t_env *env)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_destroy(&(env->start_lock1));
	pthread_mutex_destroy(&(env->start_lock2));
	pthread_mutex_destroy(&(env->print_lock));
	while (i < env->nb_philo)
	{
		pthread_mutex_destroy(&(env->philos[i]->eat_lock));
		pthread_mutex_destroy(&(env->philos[i]->left_fork));
		i++;
	}
}

void	free_all(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_philo)
		free(env->philos[i++]);
	free(env->philos);
}
