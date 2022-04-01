/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:40:46 by jchene            #+#    #+#             */
/*   Updated: 2022/04/01 15:18:55 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_charset(char *argv, const char *charset)
{
	unsigned int	i;

	i = 0;
	while (argv[i])
	{
		if (!is_charset(charset, argv[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (check_charset(argv[i], "0123456789") == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	get_input(int argc, char **argv, t_philo *philo)
{
	philo->nb_philo = ft_atoi(argv[1]);
	philo->death_time = ft_atoi(argv[2]);
	philo->eat_time = ft_atoi(argv[3]);
	philo->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		philo->max_eat = ft_atoi(argv[5]);
	else
		philo->max_eat = -1;
	return (0);
}
