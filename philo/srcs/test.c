/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:48:41 by jchene            #+#    #+#             */
/*   Updated: 2022/04/11 18:39:55 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*int	main(int argc, char **argv)
{
	t_philo			philo;
	struct timeval	time;

	(void)argc;
	philo.live = 1;
	pthread_mutex_init(&(philo.live_lock), NULL);
	gettimeofday(&time, NULL);
	msleep(ft_atou(argv[1]), &philo);
	printf("diff: %u\n", get_ms_dif(time));
	pthread_mutex_destroy(&(philo.live_lock));
	return (0);
}*/

int	main(int argc, char **argv)
{
	(void)argc;
	ft_putnbr(ft_atou(argv[1]));
	return (0);
}
