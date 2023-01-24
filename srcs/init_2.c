/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 21:31:44 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/20 21:40:39 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_forks(t_philos *philo, int i)
{
	philo->r_fork = &philo->info->forks[i];
	philo->l_fork = &philo->info->forks[(i + 1) % philo->info->nbr_of_philos];
	philo->r_fork_free = &philo->info->fork_available[i];
	philo->l_fork_free
		= &philo->info->fork_available[(i + 1) % philo->info->nbr_of_philos];
}
