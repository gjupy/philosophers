/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:07:49 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/31 12:19:35 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_time(void)
{
	static struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

bool	check_death_state(t_info *info)
{
	pthread_mutex_lock(info->death_lock);
	if (info->died == true)
	{
		pthread_mutex_unlock(info->death_lock);
		return (true);
	}
	pthread_mutex_unlock(info->death_lock);
	return (false);
}
