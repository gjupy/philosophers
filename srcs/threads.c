/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:40:54 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/20 13:41:30 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// void	start_routine(t_philos *philo)
// {
// 	philo->info->start = get_time();
// 	if (philo->philo_id % 2 == 0)
// 		while (philo->info->start + philo->info->time_to_eat >= get_time());
// 	while (true)
// 	{
// 		if (check_death_state(philo->info) == true)
// 			return ;
// 		if (check_death_state(philo->info) == false)
// 			philo_eat(philo);
// 		if (check_death_state(philo->info) == false)
// 			philo_sleep(philo);
// 	}
// }

// void	start_routine(t_philos *philo)
// {
// 	pthread_mutex_lock(philo->info->time_lock);
// 	if (philo->info->start == 0)
// 		philo->info->start = get_time();
// 	pthread_mutex_unlock(philo->info->time_lock);
// 	philo->last_meal = get_time();
// 	if (philo->philo_id % 2 == 0)
// 	{
// 		philo_think(philo);
// 		ft_sleep(philo->info->time_to_eat);
// 	}
// 	pthread_mutex_lock(philo->info->death_lock);
// 	while (philo->info->died == false && check_death_2(philo) == false 
// 			&& check_all_full(philo->info) == false)
// 	{
// 		pthread_mutex_unlock(philo->info->death_lock);
// 		// if (check_death(philo) == false)
// 		// {
// 			// pthread_mutex_lock(philo->info->death_lock);
// 			// if (philo->info->died == false)
// 			// {
// 				// pthread_mutex_unlock(philo->info->death_lock);
// 				if (philo->state != FINISHED)
// 				{
// 					if (philo->state == RUNNING || philo->state == THINKING)
// 						philo_eat(philo);
// 					else if (philo->state == EATING)
// 						philo_sleep(philo);
// 					else if (philo->state == SLEEPING)
// 						philo_think(philo);
// 				// }
// 			// pthread_mutex_unlock(philo->info->death_lock);
// 		}
// 		pthread_mutex_lock(philo->info->death_lock);
// 	}
// 	pthread_mutex_unlock(philo->info->death_lock);
// }

void	start_routine(t_philos *philo)
{
	philo->last_meal = get_time();
	if (philo->philo_id % 2 == 0)
	{
		philo_think(philo);
		ft_sleep(philo->info->time_to_eat);
	}
	while (philo->info->died == false && check_all_full(philo->info) == false)
	{
		if (check_death(philo) == false && philo->info->died == false)
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
		usleep(50);
	}
}

void	*routine(void *arg)
{
	t_philos		*philo;

	philo = (t_philos *)arg;
	while (philo->info->wait == true) // warten, sodass alle zusammen anfangen
		usleep(50);
	pthread_mutex_lock(philo->info->time_lock);
	if (philo->info->start == 0)
		philo->info->start = get_time();
	pthread_mutex_unlock(philo->info->time_lock);
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
	// ft_sleep(info->time_to_die - (info->time_to_die / 4));
	// check_death_eating(info);
	// death_checker(info);
	i = -1;
	while (++i < info->nbr_of_philos)
	{
		if (pthread_join(info->philos[i].t_id, NULL) != 0)
			err();
	}
}
