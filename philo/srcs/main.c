/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:14:52 by jchene            #+#    #+#             */
/*   Updated: 2022/04/15 15:47:30 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned int	solo_philo(t_philo *philo)
{
	if (&(philo->left_fork) == philo->right_fork)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc < 5 || argc > 6)
		return (-1);
	if (check_input(argc, argv) == -1)
		return (-1);
	if (get_input(argc, argv, &env) == -1)
		return (-1);
	start_simul(&env);
	destroy_mutexes(&env);
	free_all(&env);
	return (0);
}
