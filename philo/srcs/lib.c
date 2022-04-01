/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:42:39 by jchene            #+#    #+#             */
/*   Updated: 2022/04/01 15:17:02 by jchene           ###   ########.fr       */
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

unsigned int	is_charset(const char *charset, char c)
{
	unsigned int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

unsigned int	ft_atoi(char *str)
{
	unsigned long long	ret;
	unsigned int		i;

	ret = 0;
	i = 0;
	while (str[i])
	{
		ret += str[i] - '0';
		ret *= 10;
		i++;
	}
	ret /= 10;
	if (ret > UINT_MAX)
		return (UINT_MAX);
	printf("atoi: %d\n", (unsigned int)ret);
	return ((unsigned int)ret);
}
