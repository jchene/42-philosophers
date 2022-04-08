/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:40:10 by jchene            #+#    #+#             */
/*   Updated: 2022/04/08 15:43:50 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*unsigned int	get_s_dif(struct timeval s_time)
{
}*/

unsigned int	get_ms_dif(struct timeval s_time)
{
	time_t			sec;
	suseconds_t		usec;
	unsigned int	ms_dif;
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	sec = timestamp.tv_sec - s_time.tv_sec;
	usec = timestamp.tv_usec - s_time.tv_usec;
	ms_dif = ((unsigned int)sec * 1000) + ((unsigned int)usec / 1000);
	return (ms_dif);
}
