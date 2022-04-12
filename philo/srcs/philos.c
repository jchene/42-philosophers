/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:23:39 by jchene            #+#    #+#             */
/*   Updated: 2022/04/12 18:37:00 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_life(t_philo *philo)
{
	pthread_mutex_lock(&(philo->live_lock));
	if (philo->live != 1)
		return (pthread_mutex_unlock(&(philo->live_lock)) - 1);
	return (pthread_mutex_unlock(&(philo->live_lock)));
}

int	check_fork_drop(t_philo *philo, unsigned int fork)
{
	pthread_mutex_lock(&(philo->live_lock));
	if (philo->live != 1)
	{
		if (fork == FIRST)
		{
			if (philo->id % 2)
				pthread_mutex_unlock(&(philo->left_fork));
			else
				pthread_mutex_unlock(philo->right_fork);
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
	while ((philo->max_meal < 0)
		|| ((long)philo->nb_meal < (long)philo->max_meal))
	{
		if (check_life(philo) == -1)
			break ;
		get_fork(philo, FIRST);
		if (check_fork_drop(philo, FIRST) == -1)
			break ;
		get_fork(philo, LAST);
		if (check_fork_drop(philo, LAST) == -1)
			break ;
		set_var(&(philo->eating_lock), &(philo->is_eating), 1);
		print_state(philo, EAT);
		msleep(philo->eat_time);
		set_eat_time(philo);
		drop_forks(philo);
		set_var(&(philo->eating_lock), &(philo->is_eating), 0);
		print_state(philo, SLEEP);
		if (mcheck_sleep(philo->sleep_time, philo) == -1)
			break ;
		print_state(philo, THINK);
		usleep(50);
		philo->nb_meal++;
	}
	print_state(philo, DIE);
	pthread_exit(NULL);
}

void	reaper_routine(t_reaper *reaper)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	try_lock(reaper->start_lock);
	while (1)
	{
		i = i % reaper->nb_philo;
		pthread_mutex_lock(&(reaper->philos[i]->eat_lock));
		pthread_mutex_lock(&(reaper->philos[i]->eating_lock));
		if (((get_ms_dif(reaper->philos[i]->last_eat)) > reaper->death_time)
			&& (reaper->philos[i]->is_eating == 0))
		{
			pthread_mutex_unlock(&(reaper->philos[i]->eat_lock));
			pthread_mutex_unlock(&(reaper->philos[i]->eating_lock));
			reaper->dead_id = reaper->philos[i]->id;
			while (j < reaper->nb_philo)
			{
				set_var(&(reaper->philos[j]->live_lock),
					&(reaper->philos[j]->live), 0);
				j++;
			}
			break ;
		}
		else
		{
			pthread_mutex_unlock(&(reaper->philos[i]->eat_lock));
			pthread_mutex_unlock(&(reaper->philos[i]->eating_lock));
		}
		usleep(100);
		i++;
	}
	i = 0;
	while (i < reaper->nb_philo)
	{
		pthread_join(reaper->philos[i]->thread, NULL);
		i++;
	}
	print_state(reaper->philos[reaper->dead_id], DIE);
	pthread_exit(NULL);
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
		pthread_create(&(env->philos[i]->thread), NULL, (void *)routine,
			(void *)env->philos[i]);
		i++;
	}
	link_forks(env);
	init_reaper(env, &(env->reaper));
	pthread_create(&(env->reaper.thread), NULL, (void *)reaper_routine,
		(void *)&(env->reaper));
	pthread_mutex_unlock(&(env->start_lock));
	pthread_join(env->reaper.thread, NULL);
	print_state(env->reaper.philos[env->reaper.dead_id - 1], DIE);
}
