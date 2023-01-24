/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:07:49 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/20 21:45:41 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	get_time(void)
{
	struct timeval	time;
	time_t			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	return (ms);
}

void	ft_sleep(long long ms)
{
	long long	stop;

	stop = get_time() + ms;
	if (ms > 6)
	{
		usleep((ms - 6) * 1000);
		while (stop > get_time())
			;
	}
	else
	{
		while (stop > get_time())
			usleep(50);
	}
}
