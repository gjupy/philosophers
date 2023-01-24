/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:40:54 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/20 21:49:18 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_do_stuff(t_philos *philo)
{
	if (check_death(philo) == false)
	{
		if (philo->state != FINISHED)
		{
			if (philo->state == RUNNING || philo->state == THINKING)
				philo_eat(philo);
			else if (philo->state == EATING)
				philo_sleep(philo);
			else if (philo->state == SLEEPING)
				philo_think(philo);
		}
	}
}

void	start_routine(t_philos *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		philo_think(philo);
		ft_sleep(philo->time_to_eat);
	}
	while (check_all_full(philo) == false)
	{
		if (check_death_state(philo->info) == true)
			break ;
		philo_do_stuff(philo);
		usleep(50);
	}
}

void	*routine(void *arg)
{
	t_philos		*philo;

	philo = (t_philos *)arg;
	while (philo->info->wait == true)
		usleep(50);
	if (philo->philo_id == 1)
		philo->info->start = get_time();
	pthread_mutex_lock(&philo->info->time_lock);
	philo->start_time = philo->info->start;
	pthread_mutex_unlock(&philo->info->time_lock);
	philo->last_meal = philo->start_time;
	philo->state = RUNNING;
	start_routine(philo);
	return (NULL);
}

int	start_threads(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nbr_of_philos)
	{
		if (pthread_create
			(&info->philos[i].t_id, NULL, &routine, &info->philos[i]) != 0)
			return (EXIT_FAILURE);
	}
	info->wait = false;
	i = -1;
	while (++i < info->nbr_of_philos)
	{
		if (pthread_join(info->philos[i].t_id, NULL) != 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
