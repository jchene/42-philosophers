/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:14:03 by jchene            #+#    #+#             */
/*   Updated: 2022/04/11 18:46:19 by jchene           ###   ########.fr       */
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

# define FIRST	1
# define LAST	2

# define FORK	1
# define EAT	2
# define SLEEP	3
# define THINK	4
# define DIE	5

//PHILOSOPHERS
typedef struct s_philosophers
{
	unsigned int	eat_time;
	unsigned int	sleep_time;
	int				max_meal;

	unsigned int	nb_meal;
	struct timeval	start_time;

	unsigned int	id;
	pthread_t		thread;

	struct timeval	last_eat;
	pthread_mutex_t	eat_lock;
	unsigned int	live;
	pthread_mutex_t	live_lock;

	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;

	pthread_mutex_t	*start_lock;
	pthread_mutex_t	*print_lock;
}				t_philo;

//REAPER
typedef struct s_reaper
{
	unsigned int	nb_philo;
	unsigned int	death_time;
	unsigned int	dead_id;

	t_philo			**philos;
	pthread_t		thread;

	pthread_mutex_t	*start_lock;
}				t_reaper;

//ENVIRONMENT
typedef struct s_environment
{
	unsigned int	eat_time;
	unsigned int	sleep_time;
	int				max_meal;

	unsigned int	nb_philo;
	unsigned int	death_time;

	struct timeval	start_time;

	t_philo			**philos;
	t_reaper		reaper;

	pthread_mutex_t	start_lock;
	pthread_mutex_t	print_lock;
}				t_env;

//LIB
unsigned int	ft_strlen(char *str);
unsigned int	is_charset(const char *charset, char c);
unsigned int	ft_atou(char *str);

//INPUT
int				check_charset(char *argv, const char *charset);
int				check_input(int argc, char **argv);
int				get_input(int argc, char **argv, t_env *env);

//SIMULATION INIT
void			init_env(t_env *env);
void			init_philo(t_env *env, t_philo *philo, unsigned int i);
void			link_forks(t_env *env);
void			init_reaper(t_env *env, t_reaper *reaper);

//CORE CODE
int				check_fork_drop(t_philo *philo, unsigned int fork);
void			routine(t_philo *philo);
void			reaper_routine(t_reaper *reaper_data);
void			start_simul(t_env *env);

//ROUTINE MUTEX
void			try_lock(pthread_mutex_t *lock);
void			set_eat_time(t_philo *philo);
void			get_fork(t_philo *philo, unsigned int fork);
void			drop_forks(t_philo *philo);

//PRINTING
void			ft_putstr(char *str);
void			ft_putnbr(unsigned int nb);
void			print_state(t_philo *philo, unsigned int state);

//TIME MANAGEMENT
unsigned int	get_ms_dif(struct timeval s_time);
int				msleep(unsigned int wait, t_philo *philo, unsigned int type);

//MEMORY MANAGEMENT
void			*ft_calloc(size_t size);
void			destroy_mutexes(t_env *env);
void			free_all(t_env *env);

#endif