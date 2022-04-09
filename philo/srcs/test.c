/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:35:51 by jchene            #+#    #+#             */
/*   Updated: 2022/04/09 18:46:31 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	routine2(pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t		thread;
	pthread_mutex_t	lock;

	pthread_mutex_init(&lock, NULL);
	pthread_create(&thread, NULL, (void *)routine2, (void *)&lock);
	pthread_join(thread, NULL);
	usleep(100);
	pthread_mutex_destroy(&lock);
	return (0);
}
