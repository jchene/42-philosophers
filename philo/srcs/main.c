/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:14:52 by jchene            #+#    #+#             */
/*   Updated: 2022/04/14 17:09:07 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_state(t_philo *philo, const char *str)
{
	pthread_mutex_lock(philo->print_lock);
	printf("[%u] philo %u %s\n", get_ms_dif(philo->start_time), philo->id, str);
	pthread_mutex_unlock(philo->print_lock);
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
