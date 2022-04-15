/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:23:39 by jchene            #+#    #+#             */
/*   Updated: 2022/04/15 14:30:18 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned int	check_life(t_philo *philo)
{
	pthread_mutex_lock(&(philo->live_lock));
	return (philo->live + pthread_mutex_unlock(&(philo->live_lock)));
}

unsigned int	check_others(t_philo *philo)
{
	pthread_mutex_lock(&(philo->live_lock));
	return (philo->all_alive + pthread_mutex_unlock(&(philo->live_lock)));
}

void	routine(t_philo *philo)
{
	try_lock(philo->start_lock);
	while (check_life(philo) && check_others(philo))
	{
		get_first_fork(philo);
		if (check_fork_drop(philo, 1) == -1)
			break ;
		get_last_fork(philo);
		if (check_fork_drop(philo, 2) == -1)
			break ;
		set_last_eat(philo);
		print_state(philo, "is eating");
		if (!mcheck_sleep(philo->eat_time, philo))
			break ;
		set_last_eat(philo);
		drop_forks(philo);
		print_state(philo, "is sleeping");
		if (!mcheck_sleep(philo->sleep_time, philo))
			break ;
		print_state(philo, "is thinking");
		usleep(42);
		philo->nb_meal++;
	}
	if (!check_life(philo))
		print_state(philo, "died");
	pthread_exit(NULL);
}

void	reaper_routine(t_reaper *rp)
{
	try_lock(rp->start_lock);
	while (1)
	{
		rp->loc_id = rp->loc_id % rp->nb_philo;
		if ((rp->max_meal > 0) && ((int)get_nb_meal(rp->philos[rp->loc_id])
				>= rp->max_meal))
			rp->done_eating++;
		if (check_done(rp))
			break ;
		pthread_mutex_lock(&(rp->philos[rp->loc_id]->eat_lock));
		if ((get_ms_dif(rp->philos[rp->loc_id]->last_eat)) > rp->death_time)
		{
			pthread_mutex_unlock(&(rp->philos[rp->loc_id]->eat_lock));
			pthread_mutex_lock(&(rp->philos[rp->loc_id]->live_lock));
			rp->philos[rp->loc_id]->live = 0;
			pthread_mutex_unlock(&(rp->philos[rp->loc_id]->live_lock));
			kill_all(rp);
			break ;
		}
		pthread_mutex_unlock(&(rp->philos[rp->loc_id]->eat_lock));
		usleep(42);
		rp->loc_id++;
	}
	join_all(rp);
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
