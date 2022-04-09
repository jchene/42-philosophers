/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:05:40 by jchene            #+#    #+#             */
/*   Updated: 2022/04/09 15:20:27 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	get_data_cpy(t_data *src, t_data *dst)
{
	dst->nb_philo = src->nb_philo;
	dst->eat_time = src->eat_time;
	dst->max_eat = src->max_eat;
	dst->death_time = src->death_time;
	dst->sleep_time = src->sleep_time;
	dst->start_time = src->start_time;
}

void	init_philo(t_data *data, t_env *env, unsigned int i)
{
	get_data_cpy(data, &(env->philos[i]->data_cpy));
	env->philos[i]->philo_id = i + 1;
	if (i == 0)
		env->philos[i]->left_fork = env->forks[data->nb_philo - 1];
	else
		env->philos[i]->left_fork = env->forks[i - 1];
	env->philos[i]->right_fork = env->forks[i];
	env->philos[i]->start_lock = &(env->start_lock);
}

void	init_env(t_data *data, t_env *env)
{
	unsigned int	i;

	i = 0;
	env->philos = ft_calloc(sizeof(t_philo *) * data->nb_philo);
	env->threads = ft_calloc(sizeof(pthread_t *) * data->nb_philo);
	env->forks = ft_calloc(sizeof(pthread_mutex_t *) * data->nb_philo);
	while (i < data->nb_philo)
	{
		env->philos[i] = ft_calloc(sizeof(t_philo));
		env->philos[i]->thread = ft_calloc(sizeof(pthread_t));
		env->forks[i] = ft_calloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(env->forks[i], NULL);
		env->philos[i]->last_eat = ft_calloc(sizeof(struct timeval));
		i++;
	}
}

void	set_start_time(t_data *data, t_env *env, t_reaper *reaper_data)
{
	unsigned int	i;
	struct timeval	timestamp;

	i = 0;
	gettimeofday(&timestamp, NULL);
	data->start_time = timestamp;
	reaper_data->data_cpy.start_time = timestamp;
	while (i < data->nb_philo)
	{
		env->philos[i]->data_cpy.start_time = timestamp;
		i++;
	}
}
