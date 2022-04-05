/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:16:24 by jchene            #+#    #+#             */
/*   Updated: 2022/04/05 17:17:08 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_calloc(size_t size)
{
	return (memset((malloc(size)), 0, size));
}

t_free	*get_all(void)
{
	static t_free	all;

	return (&all);
}

int	free_data(int ret, t_data *data)
{
	free(data);
	return (ret);
}

int	free_all(int ret)
{
	free(get_all()->data);
	return (ret);
}
