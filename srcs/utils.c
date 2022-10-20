/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:07:49 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/19 21:37:41 by gjupy            ###   ########.fr       */
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

void    ft_sleep(long long ms)
{
    long long   stop;

    stop = get_time() + ms;
    if (ms > 6)
    {
        usleep((ms - 6) * 1000);
        while (stop > get_time());
    }
    else
    {
        while (stop > get_time())
            usleep(50);
    }
}

// void	ft_sleep(time_t val)
// {
// 	time_t	target;

// 	target = get_time() + val;
// 	while (get_time() < target)
// 		usleep(50);
// }