/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:39:38 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/20 22:02:13 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (parser_input_errors(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init(argv, &info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (start_threads(&info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	free_all(&info);
	return (EXIT_SUCCESS);
}
