/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:05:40 by jchene            #+#    #+#             */
/*   Updated: 2022/04/09 21:32:50 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_env(t_env *env)
{
	unsigned int	i;

	i = 0;
	env->philos = ft_calloc(sizeof(t_philo *) * env->nb_philo);
	while (i < env->nb_philo)
		env->philos[i++] = ft_calloc(sizeof(t_philo));
	pthread_mutex_init(&(env->start_lock), NULL);
	pthread_mutex_init(&(env->print_lock), NULL);
	gettimeofday(&(env->start_time), NULL);
}

void	init_philo(t_env *env, t_philo *philo, unsigned int i)
{
	philo->eat_time = env->eat_time;
	philo->sleep_time = env->sleep_time;
	philo->max_meal = env->max_meal;
	philo->nb_meal = 0;
	philo->start_time = env->start_time;
	philo->id = i + 1;
	philo->last_eat = env->start_time;
	pthread_mutex_init(&(philo->eat_lock), NULL);
	philo->live = 1;
	pthread_mutex_init(&(philo->live_lock), NULL);
	pthread_mutex_init(&(philo->right_fork), NULL);
	philo->start_lock = &(env->start_lock);
	philo->start_lock = &(env->print_lock);
}

void	link_forks(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_philo)
	{
		env->philos[i]->right_fork
			= &(env->philos[((i + 1) % env->nb_philo)]->left_fork);
		i++;
	}
}

void	init_reaper(t_env *env, t_reaper *reaper)
{
	reaper->nb_philo = env->nb_philo;
	reaper->death_time = env->death_time;
	reaper->philos = env->philos;
	reaper->start_lock = &(env->start_lock);
	reaper->dead_id = 0;
}

void	init_join(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_philo)
		pthread_join(env->philos[i++]->thread, NULL);
	pthread_join(env->reaper.thread, NULL);
}
