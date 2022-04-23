/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:23:39 by jchene            #+#    #+#             */
/*   Updated: 2022/04/23 18:14:13 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(t_philo *philo)
{
	try_lock(philo->start_lock);
	set_last_eat(philo);
	while (philo->live && philo->all_alive)
	{
		get_first_fork(philo);
		if (check_fork_drop(philo, 1) == -1)
			break ;
		get_last_fork(philo);
		if (check_fork_drop(philo, 2) == -1)
			break ;
		set_last_eat(philo);
		print_state(philo, "is eating");
		if (!mcheck_sleep(philo->eat_time, philo, 2))
			break ;
		drop_forks(philo);
		print_state(philo, "is sleeping");
		if (!mcheck_sleep(philo->sleep_time, philo, 0))
			break ;
		print_state(philo, "is thinking");
		philo->nb_meal++;
	}
	return (NULL);
}

void	*reaper_routine(t_reaper *rp)
{
	try_lock(rp->start_lock);
	while (1)
	{
		rp->loc_id = rp->loc_id % rp->nb_philo;
		if (check_all_done(rp))
		{
			kill_all(rp);
			break ;
		}
		if (check_death_time(rp))
		{
			execute(rp);
			break ;
		}
		usleep(1000);
		rp->loc_id++;
	}
	join_all(rp);
	if (!check_all_done(rp))
		print_state(rp->philos[(rp->dead_id - 1) % rp->nb_philo], "died");
	return (NULL);
}

void	start_simul(t_env *env)
{
	unsigned int	i;

	i = 0;
	init_env(env);
	pthread_mutex_lock(&(env->start_lock1));
	pthread_mutex_lock(&(env->start_lock2));
	init_reaper(env, &(env->reaper));
	pthread_create(&(env->reaper.thread), NULL, (void *)reaper_routine,
		(void *)&(env->reaper));
	gettimeofday(&(env->start_time), NULL);
	while (i < env->nb_philo)
	{
		env->philos[i]->start_time = env->start_time;
		pthread_create(&(env->philos[i]->thread), NULL, (void *)routine,
			(void *)env->philos[i]);
		i++;
	}
	pthread_mutex_unlock(&(env->start_lock1));
	usleep(5000);
	pthread_mutex_unlock(&(env->start_lock2));
	pthread_join(env->reaper.thread, NULL);
}
