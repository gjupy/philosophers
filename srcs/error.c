/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:40:03 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/16 14:56:42 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	malloc_err(void)
{
	ft_putstr_fd("\033[31mERROR\033[0m\n", 2);
	ft_putstr_fd("failed to allocate mem\n", 2);
	exit(EXIT_FAILURE);
}

void	err(void)
{
 	ft_putstr_fd("\033[31mERROR\033[0m\n", 2);
	ft_putstr_fd("how to run philo: ./philo nbr_of_philosophers time_to_die\
 time_to_eat time_to_sleep\
 [nbr_of_times_each_philosopher_must_eat]\n", 2);
	exit(EXIT_FAILURE);
}
