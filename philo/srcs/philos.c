/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:23:39 by jchene            #+#    #+#             */
/*   Updated: 2022/04/14 18:02:02 by jchene           ###   ########.fr       */
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
	while ((philo->max_meal < 0) || (philo->nb_meal < philo->max_meal))
	{
		if (check_life(philo) == -1)
			break ;
		get_first_fork(philo);
		if (check_fork_drop(philo, FIRST) == -1)
			break ;
		get_last_fork(philo);
		set_var(&(philo->eating_lock), &(philo->is_eating), 1);
		set_eat_time(philo);
		print_state(philo, "is eating");
		msleep(philo->eat_time);
		set_var(&(philo->eating_lock), &(philo->is_eating), 0);
		drop_forks(philo);
		print_state(philo, "is sleeping");
		if (mcheck_sleep(philo->sleep_time, philo) == -1)
			break ;
		print_state(philo, "is thinking");
		usleep(42);
		philo->nb_meal++;
	}
	if (philo->nb_meal != philo->max_meal)
		print_state(philo, "has died");
	pthread_exit(NULL);
}

void	reaper_routine(t_reaper *reaper)
{
	unsigned int	i;

	i = 0;
	try_lock(reaper->start_lock);
	while (1)
	{
		i = i % reaper->nb_philo;
		get_eat_locks(reaper->philos[i]);
		if (((get_ms_dif(reaper->philos[i]->last_eat)) > reaper->death_time)
			&& (reaper->philos[i]->is_eating == 0))
		{
			drop_eat_locks(reaper->philos[i]);
			reaper->dead_id = reaper->philos[i]->id;
			kill_all(reaper);
			break ;
		}
		else
			drop_eat_locks(reaper->philos[i]);
		usleep(42);
		i++;
	}
	join_all(reaper);
	pthread_exit(NULL);
}

void	start_simul(t_env *env)
{
	unsigned int	i;

	i = 0;
	init_env(env);
	pthread_mutex_lock(&(env->start_lock1));
	pthread_mutex_lock(&(env->start_lock2));
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
	pthread_mutex_unlock(&(env->start_lock1));
	usleep(42);
	pthread_mutex_unlock(&(env->start_lock2));
	pthread_join(env->reaper.thread, NULL);
}
