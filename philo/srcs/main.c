/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:14:52 by jchene            #+#    #+#             */
/*   Updated: 2022/04/05 18:05:00 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_env	*env;

	if (argc < 5 || argc > 6)
		return (-1);
	if (check_input(argc, argv) == -1)
		return (-1);
	data = (t_data *)malloc(sizeof(t_data) + 1);
	if (!memset((void *)data, 0, sizeof(t_data) + 1))
		return (-1);
	get_all()->data = data;
	if (get_input(argc, argv, data) == -1)
		return (free_data(-1, data));
	env = (t_env *)malloc(sizeof(t_env) + 1);
	if (!memset((void *)env, 0, sizeof(t_env) + 1))
		return (free_all(-1));
	get_all()->env = env;
	if (get_env(data, env) == -1)
		return (free_all(-1));
	while (1)
	{
		(void)env;
	}
	free_all(0);
	return (0);
}
