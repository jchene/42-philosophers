/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:23:39 by jchene            #+#    #+#             */
/*   Updated: 2022/04/05 18:07:04 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(t_philo *tmp)
{
	unsigned int	i;

	i = 0;

	pthread_mutex_lock(tmp->start_lock);
	pthread_mutex_unlock(tmp->start_lock);
	printf("philo %d is living!\n", tmp->philo_id);
	while (i < tmp->data_cpy.max_eat)
	{
		printf("philo %d is eating\n", tmp->philo_id);
		usleep(100000);
		printf("philo %d is thinking\n", tmp->philo_id);
		usleep(100000);
		printf("philo %d is sleeping\n", tmp->philo_id);
		usleep(100000);
		i++;
	}
	pthread_exit(NULL);
}

void	init_philo(t_data *data, t_philo *tmp, t_env *env)
{
	tmp->data_cpy.nb_philo = data->nb_philo;
	tmp->data_cpy.death_time = data->death_time;
	tmp->data_cpy.eat_time = data->eat_time;
	tmp->data_cpy.sleep_time = data->sleep_time;
	tmp->data_cpy.max_eat = data->max_eat;
	tmp->start_lock = &(env->start_lock);
}

int	get_env(t_data *data, t_env *env)
{
	unsigned int	i;
	t_philo			*tmp;

	i = 0;
	env->philos = ft_calloc(sizeof(t_philo *) * data->nb_philo);
	env->threads = ft_calloc(sizeof(pthread_t *) * data->nb_philo);
	env->forks = ft_calloc(sizeof(unsigned int *) * data->nb_philo);
	pthread_mutex_init(&(env->start_lock), NULL);

	pthread_mutex_lock(&(env->start_lock));
	while (i < data->nb_philo)
	{
		tmp = ft_calloc(sizeof(t_philo));
		tmp->thread = ft_calloc(sizeof(pthread_t));
		tmp->philo_id = i;
		init_philo(data, tmp, env);
		pthread_create(tmp->thread, NULL, (void *)routine, (void *)tmp);
		env->threads[i] = tmp->thread;
		env->philos[i] = tmp;
		env->forks[i] = 0;
		i++;
	}
	printf("finished!\n");
	pthread_mutex_unlock(&(env->start_lock));
	return (0);
}
