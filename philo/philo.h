/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:14:03 by jchene            #+#    #+#             */
/*   Updated: 2022/04/05 18:03:03 by jchene           ###   ########.fr       */
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

//CONSTANTS
typedef struct s_data
{
	unsigned int	nb_philo;
	unsigned int	death_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	unsigned int	max_eat;
}				t_data;

//PHILOSOPHERS INNER DATA
typedef struct s_philosophers
{
	t_data			data_cpy;
	unsigned int	philo_id;
	pthread_t		*thread;
	pthread_mutex_t	*start_lock;
}				t_philo;

//ENVIRONMENT DATA
typedef struct s_environment
{
	t_philo			**philos;
	pthread_t		**threads;
	unsigned int	**forks;
	pthread_mutex_t	start_lock;
}				t_env;

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

//ENVIRONMENT
int				get_env(t_data *data, t_env *env);
void			init_philo(t_data *data, t_philo *tmp, t_env *env);
void			*routine(t_philo *tmp);
#endif