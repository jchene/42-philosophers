/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:23:39 by jchene            #+#    #+#             */
/*   Updated: 2022/04/06 16:25:43 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*od_routine(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(philo->start_lock);
	pthread_mutex_unlock(philo->start_lock);
	printf("philo %d is living!\n", philo->philo_id);
	while (i < philo->data_cpy.max_eat)
	{
		printf("philo %d is thinking\n", philo->philo_id);
		usleep(50);
		pthread_mutex_lock(philo->left_fork);
		printf("philo %d has taken his left fork\n", philo->philo_id);
		pthread_mutex_lock(philo->right_fork);
		printf("philo %d has taken his right fork\n", philo->philo_id);
		printf("philo %d is eating\n", philo->philo_id);
		usleep(1000 * philo->data_cpy.eat_time);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		printf("philo %d is sleeping\n", philo->philo_id);
		usleep(1000 * philo->data_cpy.sleep_time);
		i++;
	}
	printf("philo %d has died\n", philo->philo_id);
	pthread_exit(NULL);
}

void	*ev_routine(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(philo->start_lock);
	pthread_mutex_unlock(philo->start_lock);
	printf("philo %d is living!\n", philo->philo_id);
	while (i < philo->data_cpy.max_eat)
	{
		printf("philo %d is thinking\n", philo->philo_id);
		usleep(100);
		pthread_mutex_lock(philo->right_fork);
		printf("philo %d has taken his right fork\n", philo->philo_id);
		pthread_mutex_lock(philo->left_fork);
		printf("philo %d has taken his left fork\n", philo->philo_id);
		printf("philo %d is eating\n", philo->philo_id);
		usleep(1000 * philo->data_cpy.eat_time);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("philo %d is sleeping\n", philo->philo_id);
		usleep(1000 * philo->data_cpy.sleep_time);
		i++;
	}
	printf("philo %d has died\n", philo->philo_id);
	pthread_exit(NULL);
}

void	init_philo(t_data *data, t_env *env, unsigned int i)
{
	env->philos[i]->data_cpy.nb_philo = data->nb_philo;
	env->philos[i]->data_cpy.death_time = data->death_time;
	env->philos[i]->data_cpy.eat_time = data->eat_time;
	env->philos[i]->data_cpy.sleep_time = data->sleep_time;
	env->philos[i]->data_cpy.max_eat = data->max_eat;
	env->philos[i]->philo_id = i;
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
		i++;
	}
}

void	get_env(t_data *data, t_env *env)
{
	unsigned int	i;

	i = 0;
	init_env(data, env);
	pthread_mutex_init(&(env->start_lock), NULL);
	pthread_mutex_lock(&(env->start_lock));
	while (i < data->nb_philo)
	{
		init_philo(data, env, i);
		if (i % 2)
			pthread_create(env->philos[i]->thread, NULL,
				(void *)od_routine, (void *)env->philos[i]);
		else
			pthread_create(env->philos[i]->thread, NULL,
				(void *)ev_routine, (void *)env->philos[i]);
		i++;
	}
	pthread_mutex_unlock(&(env->start_lock));
}
