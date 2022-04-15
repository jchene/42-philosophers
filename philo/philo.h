/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:14:03 by jchene            #+#    #+#             */
/*   Updated: 2022/04/15 14:13:12 by jchene           ###   ########.fr       */
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

# define LEFT	1
# define RIGHT	2

# define PAST	0
# define FUTURE	1

# define FIRST	1
# define LAST	2

# define FORK	1
# define EAT	2
# define SLEEP	3
# define THINK	4
# define DIE	5
# define TEST	6

//PHILOSOPHERS
typedef struct s_philosophers
{
	unsigned int	eat_time;
	unsigned int	sleep_time;
	int				max_meal;
	struct timeval	start_time;
	unsigned int	id;
	pthread_t		thread;

	int				nb_meal;
	struct timeval	last_eat;
	pthread_mutex_t	eat_lock;

	unsigned int	live;
	unsigned int	all_alive;
	pthread_mutex_t	live_lock;

	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;

	pthread_mutex_t	*start_lock;
	pthread_mutex_t	*print_lock;
}				t_philo;

//REAPER
typedef struct s_reaper
{
	unsigned int	loc_id;
	unsigned int	nb_philo;
	int				max_meal;
	unsigned int	death_time;
	unsigned int	done_eating;

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

	pthread_mutex_t	start_lock1;
	pthread_mutex_t	start_lock2;
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

//CORE CODE
unsigned int	check_life(t_philo *philo);
unsigned int	check_others(t_philo *philo);
void			routine(t_philo *philo);
void			reaper_routine(t_reaper *reaper_data);
void			start_simul(t_env *env);

//SIMULATION
void			init_env(t_env *env);
void			init_philo(t_env *env, t_philo *philo, unsigned int i);
void			link_forks(t_env *env);
void			init_reaper(t_env *env, t_reaper *reaper);

//FORKS
void			get_first_fork(t_philo *philo);
void			get_last_fork(t_philo *philo);
void			drop_first_fork(t_philo *philo);
void			drop_forks(t_philo *philo);
int				check_fork_drop(t_philo *philo, unsigned int nb_forks);

//ROUTINE MUTEX
void			try_lock(pthread_mutex_t *lock);
void			kill_all(t_reaper *reaper);
void			join_all(t_reaper *reaper);
unsigned int	check_life(t_philo *philo);

//TIME MANAGEMENT
unsigned int	get_ms_dif(struct timeval s_time);
int				msleep(unsigned int wait);
int				mcheck_sleep(unsigned int wait, t_philo *philo);

//MEMORY MANAGEMENT
void			*ft_calloc(size_t size);
void			destroy_mutexes(t_env *env);
void			free_all(t_env *env);

//EATING
void			set_last_eat(t_philo *philo);
unsigned int	get_nb_meal(t_philo *philo);
unsigned int	check_done(t_reaper *reaper);

//PRINTING
void			print_state(t_philo *philo, const char *str);

#endif