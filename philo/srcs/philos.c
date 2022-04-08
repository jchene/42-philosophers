/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:23:39 by jchene            #+#    #+#             */
/*   Updated: 2022/04/08 16:00:03 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	routine(t_philo *philo)
{
	int				i;

	i = 0;
	try_lock(philo->start_lock);
	while ((philo->data_cpy.max_eat < 0) || (i < philo->data_cpy.max_eat))
	{
		printf("[%u] philo %d is thinking\n",
			get_ms_dif(philo->data_cpy.start_time), philo->philo_id);
		usleep(50);
		get_forks(philo);
		printf("[%u] philo %d is eating\n",
			get_ms_dif(philo->data_cpy.start_time), philo->philo_id);
		get_eat_time(philo);
		usleep(1000 * philo->data_cpy.eat_time);
		drop_forks(philo);
		printf("[%u] philo %d is sleeping\n",
			get_ms_dif(philo->data_cpy.start_time), philo->philo_id);
		usleep(1000 * philo->data_cpy.sleep_time);
		i++;
	}
	printf("[%u] philo %d has died\n",
		get_ms_dif(philo->data_cpy.start_time), philo->philo_id);
	pthread_exit(NULL);
}

void	reaper_routine(t_reaper *reaper_data)
{
	int				i;

	i = 0;
	try_lock(&(reaper_data->env->start_lock));
	pthread_mutex_lock(&(reaper_data->env->stop_lock));
	while (1)
	{
		i = i % reaper_data->data_cpy.nb_philo;
		pthread_mutex_lock(&(reaper_data->env->philos[i]->eat_lock));
		if (get_ms_dif(*(reaper_data->env->philos[i]->last_eat)) > 10)
			pthread_mutex_unlock(&(reaper_data->env->stop_lock));
		pthread_mutex_unlock(&(reaper_data->env->philos[i]->eat_lock));
		i++;
	}
}

void	start_simul(t_data *data, t_env *env)
{
	unsigned int	i;
	t_reaper		reaper_data;

	i = 0;
	init_env(data, env);
	pthread_mutex_init(&(env->stop_lock), NULL);
	pthread_mutex_init(&(env->start_lock), NULL);
	pthread_mutex_lock(&(env->start_lock));
	gettimeofday(&(data->start_time), NULL);
	while (i < data->nb_philo)
	{
		init_philo(data, env, i);
		pthread_mutex_init(&(env->philos[i]->eat_lock), NULL);
		pthread_create(env->philos[i]->thread, NULL, (void *)routine,
			(void *)env->philos[i]);
		i++;
	}
	reaper_data.env = env;
	get_data_cpy(data, &(reaper_data.data_cpy));
	pthread_create(&env->reaper, NULL, (void *)reaper_routine,
		(void *)(&reaper_data));
	pthread_mutex_unlock(&(env->start_lock));
}
