/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:23:39 by jchene            #+#    #+#             */
/*   Updated: 2022/04/20 17:07:19 by jchene           ###   ########.fr       */
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

void	*routine(t_philo *philo)
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
		if (!mcheck_sleep(philo->eat_time, philo, 2))
			break ;
		drop_forks(philo);
		print_state(philo, "is sleeping");
		if (!mcheck_sleep(philo->sleep_time, philo, 0))
			break ;
		print_state(philo, "is thinking");
		usleep(42);
		pthread_mutex_lock(&(philo->eat_lock));
		philo->nb_meal++;
		pthread_mutex_unlock(&(philo->eat_lock));
	}
	return (NULL);
}

void	*reaper_routine(t_reaper *rp)
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
			execute(rp);
			break ;
		}
		pthread_mutex_unlock(&(rp->philos[rp->loc_id]->eat_lock));
		usleep(SLEEP);
		rp->loc_id++;
	}
	join_all(rp);
	if (rp->done_eating < rp->nb_philo)
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
