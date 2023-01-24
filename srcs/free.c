/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:09:49 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/20 21:38:51 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy_forks(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nbr_of_philos)
	{
		pthread_mutex_destroy(info->philos[i].l_fork);
		pthread_mutex_destroy(info->philos[i].r_fork);
	}
	i = -1;
	while (++i < info->nbr_of_philos)
		pthread_mutex_destroy(&info->forks[i]);
}

void	free_all(t_info *info)
{
	destroy_forks(info);
	pthread_mutex_destroy(&info->print_lock);
	pthread_mutex_destroy(&info->death_lock);
	pthread_mutex_destroy(&info->time_lock);
	pthread_mutex_destroy(&info->free_fork_lock);
}
