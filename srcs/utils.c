/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:07:49 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/18 20:52:31 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// size_t	get_time(void)
// {
// 	static struct timeval current_time;

// 	gettimeofday(&current_time, NULL);
// 	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
// }

// void	ft_sleep(size_t time)
// {
// 	size_t	start_time;

// 	start_time = get_time();
// 	while(start_time + time > get_time());
// }

time_t	get_time(void)
{
	struct timeval	time;
	time_t			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	return (ms);
}

void	ft_sleep(time_t val)
{
	time_t	start_time;

	start_time = get_time();
	while(start_time + val > get_time());
}