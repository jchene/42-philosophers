/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:45:44 by jchene            #+#    #+#             */
/*   Updated: 2022/04/14 17:09:17 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*void	ft_putstr(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

void	ft_putnbr(unsigned int nb)
{
	char	nb2;

	if (nb >= 10)
		ft_putnbr(nb / 10);
	nb2 = (nb % 10) + '0';
	write(1, &nb2, 1);
}*/


/*unsigned int	get_fork_id(t_philo *philo, unsigned int fork)
{
	if (fork == LEFT)
		return (philo->id);
	else if (philo->id == 4)
		return (1);
	return (philo->id + 1);
}*/

/*void	prt_fork(t_philo *philo, unsigned int fork)
{
	pthread_mutex_lock(philo->print_lock);
	printf("[%u] philo %u has taken a fork: fork %u\n",
		get_ms_dif(philo->start_time), philo->id, get_fork_id(philo, fork));
	pthread_mutex_unlock(philo->print_lock);
}*/
