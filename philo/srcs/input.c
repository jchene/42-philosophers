/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:40:46 by jchene            #+#    #+#             */
/*   Updated: 2022/04/09 20:05:49 by jchene           ###   ########.fr       */
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

int	get_input(int argc, char **argv, t_env *env)
{
	env->nb_philo = ft_atou(argv[1]);
	env->death_time = ft_atou(argv[2]);
	env->eat_time = ft_atou(argv[3]);
	env->sleep_time = ft_atou(argv[4]);
	if (argc == 6)
		env->max_meal = ft_atou(argv[5]);
	else
		env->max_meal = -1;
	return (0);
}
