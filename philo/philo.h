/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:14:03 by jchene            #+#    #+#             */
/*   Updated: 2022/04/09 15:44:37 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <pthread.h>
# include <limits.h>
# include <string.h>
# include <sys/time.h>

//CONSTANTS
typedef struct s_data
{
	unsigned int	nb_philo;
	unsigned int	death_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	int				max_eat;
	struct timeval	start_time;

}				t_data;

//PHILOSOPHERS DATA
typedef struct s_philosophers
{
	t_data			data_cpy;
	unsigned int	philo_id;
	pthread_t		*thread;
	struct timeval	*last_eat;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*start_lock;
	pthread_mutex_t	*stop_lock;
}				t_philo;

//ENVIRONMENT DATA
typedef struct s_environment
{
	t_philo			**philos;
	pthread_t		**threads;
	pthread_t		reaper;
	pthread_mutex_t	**forks;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	stop_lock;
}				t_env;

//REAPER DATA
typedef struct s_reaper
{
	t_data			data_cpy;
	t_env			*env;
}				t_reaper;

//FREE ACCESS ADDRESSES
typedef struct s_free_singleton
{
	t_data			*data;
	t_env			*env;
}				t_free;

//LIB
unsigned int	ft_strlen(char *str);
unsigned int	is_charset(const char *charset, char c);
unsigned int	ft_atou(char *str);

//INPUT
int				check_charset(char *argv, const char *charset);
int				check_input(int argc, char **argv);
int				get_input(int argc, char **argv, t_data *data);

//MEMORY MANAGEMENT
void			*ft_calloc(size_t size);
t_free			*get_all(void);
int				free_data(int ret, t_data *data);
int				free_all(int ret);

//SIMULATION INIT
void			get_data_cpy(t_data *src, t_data *dst);
void			init_philo(t_data *data, t_env *env, unsigned int i);
void			init_env(t_data *data, t_env *env);
void			set_start_time(t_data *data, t_env *env, t_reaper *reaper_data);

//CORE CODE
void			routine(t_philo *philo);
void			reaper_routine(t_reaper *reaper_data);
void			start_simul(t_data *data, t_env *env);

//ROUTINE MUTEX
void			try_lock(pthread_mutex_t *lock);
void			get_eat_time(t_philo *philo);
void			get_forks(t_philo *philo);
void			drop_forks(t_philo *philo);

//TIME MANAGEMENT
unsigned int	get_ms_dif(struct timeval s_time);
void			msleep(unsigned int wait);

#endif