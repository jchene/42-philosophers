/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:23:39 by jchene            #+#    #+#             */
/*   Updated: 2022/04/09 21:38:24 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_life(t_philo *philo, unsigned int fork)
{
	pthread_mutex_lock(&(philo->live_lock));
	if (philo->live != 1)
	{
		if (fork == FIRST)
		{
			if (philo->id % 2)
				pthread_mutex_unlock(&(philo->left_fork));
			else
				pthread_mutex_unlock(&(philo->right_fork));
		}
		else
			drop_forks(philo);
		return (-1);
	}
	pthread_mutex_unlock(&(philo->live_lock));
	return (0);
}

void	routine(t_philo *philo)
{
	try_lock(philo->start_lock);
	while ((philo->max_meal < 0) || (philo->nb_meal < philo->max_meal))
	{
		get_fork(philo, FIRST);
		if (check_life(philo, FIRST) == -1)
			break ;
		get_fork(philo, LAST);
		if (check_life(philo, LAST) == -1)
			break ;
		print_state(philo, EAT);
		set_eat_time(philo);
		if (msleep(philo->eat_time, philo) == -1)
			break ;
		drop_forks(philo);
		print_state(philo, SLEEP);
		if (msleep(philo->sleep_time, philo) == -1)
			break ;
		print_state(philo, THINK);
		usleep(50);
		philo->nb_meal++;
	}
	pthread_exit(NULL);
}

void	reaper_routine(t_reaper *reaper)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	try_lock(&(reaper->start_lock));
	while (1)
	{
		i = i % reaper->nb_philo;
		pthread_mutex_lock(&(reaper->philos[i]->eat_lock));
		if ((get_ms_dif(reaper->philos[i]->last_eat)) > 10)
		{
			reaper->dead_id = reaper->philos[i]->id;
			while (j < reaper->nb_philo)
			{
				pthread_mutex_lock(&(reaper->philos[j]->live_lock));
				reaper->philos[j]->live = 0;
				pthread_mutex_unlock(&(reaper->philos[j]->live_lock));
				j++;
			}
		}
		pthread_mutex_unlock(&(reaper->philos[i]->eat_lock));
		print_state(reaper->philos[i], DIE);
		i++;
	}
}

void	start_simul(t_env *env)
{
	unsigned int	i;

	i = 0;
	init_env(env);
	pthread_mutex_lock(&(env->start_lock));
	while (i < env->nb_philo)
	{
		init_philo(env, env->philos[i], i);
		pthread_create(env->philos[i]->thread, NULL, (void *)routine,
			(void *)env->philos[i]);
		i++;
	}
	link_forks(env);
	init_reaper(env, &(env->reaper));
	pthread_create(&(env->reaper.thread), NULL, (void *)reaper_routine,
		(void *)&(env->reaper));
	init_join(env);
	pthread_mutex_unlock(&(env->start_lock));
}
