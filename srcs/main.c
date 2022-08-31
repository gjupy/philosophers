/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:39:38 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/31 15:32:25 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// static int	ft_terminate(t_philos *philos)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < philos->info->nbr_of_philos)
// 	{
// 		if (pthread_detach(philos[i].t_id) != 0)
// 			err();
// 	}
// 	// free_all(philos, input);
// 	return (EXIT_SUCCESS);
// }

int	main(int argc, char **argv)
{
	t_info info;

	parser_input_errors(argc, argv);
	init(argv, &info);
	start_threads(&info);
	// ft_terminate(info.philos);
	free_all(&info);
	return (0);
}
