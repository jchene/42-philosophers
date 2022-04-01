/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:14:52 by jchene            #+#    #+#             */
/*   Updated: 2022/04/01 13:26:12 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_charset(char *argv, const char *charset)
{
	unsigned int	i;

	i = 0;
	while (argv[i])
	{
		if (is_charset(charset, argv[i]) == -1)
			return (-1);
		i++;
	}
}

int	check_input(int argc, char **argv)
{
	unsigned int	i;

	i = 1;
	while (i < argc)
	{
		if (check_charset(argv[i], "0123456789") == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	**threads;
	int			ret;

	if (argc < 4 || argc > 5)
		return (-1);
	if (check_input(argc, argv) == -1)
		return (-1);
	return (0);
}
