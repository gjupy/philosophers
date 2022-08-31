/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:09:49 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/31 15:07:43 by gjupy            ###   ########.fr       */
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
		// free(info->philos[i].r_fork);
		// free(info->philos[i].l_fork);
		// kriege bei beides "error: pointer being free was not allocated"
	}
}

void	free_all(t_info *info)
{
	destroy_forks(info);
	pthread_mutex_destroy(info->print_lock);
	free(info->print_lock);
	pthread_mutex_destroy(info->death_lock);
	free(info->death_lock);
	pthread_mutex_destroy(info->time_lock);
	free(info->time_lock);
	// pthread_mutex_destroy(info->eat_lock);
	// free(input->eat_lock);
	// free(input);
}