/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:14:52 by jchene            #+#    #+#             */
/*   Updated: 2022/04/01 15:17:19 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	free_philo(int ret, t_philo *philo)
{
	free(philo);
	return (ret);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (-1);
	if (check_input(argc, argv) == -1)
		return (-1);
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (-1);
	if (get_input(argc, argv, philo) == -1)
		return (free_philo(-1, philo));
	free_philo(0, philo);
	return (0);
}
