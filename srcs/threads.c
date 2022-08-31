/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:40:54 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/31 15:35:07 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	start_routine(t_philos *philo)
{
	philo->info->start = get_time();
	if (philo->philo_id % 2 == 0)
		while (philo->info->start + philo->info->time_to_eat >= get_time());
	while (true)
	{
		if (check_death_state(philo->info) == false)
			philo_eat(philo);
		if (check_death_state(philo->info) == false)
			philo_sleep(philo);
		if (check_death_state(philo->info) == true)
			return ;
	}
}

void	*routine(void *arg)
{
	t_philos		*philo;

	philo = (t_philos *)arg;
	while (philo->info->wait == true); // warten, sodass alle zusammen anfangen
	philo->state = RUNNING;
	start_routine(philo);
	return (NULL);
}

void	start_threads(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nbr_of_philos)
	{
		if (pthread_create(&info->philos[i].t_id, NULL, &routine, &info->philos[i]) != 0)
			err();
	}
	info->wait = false;
	death_checker(info);
	i = -1;
	while (++i < info->nbr_of_philos)
	{
		if (pthread_join(info->philos[i].t_id, NULL) != 0)
			err();
	}
}
