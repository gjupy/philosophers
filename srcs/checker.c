/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:29:42 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/20 21:38:18 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	check_death_state(t_info *info)
{
	pthread_mutex_lock(&info->death_lock);
	if (info->died == true)
	{
		pthread_mutex_unlock(&info->death_lock);
		return (true);
	}
	pthread_mutex_unlock(&info->death_lock);
	return (false);
}

bool	check_death(t_philos *philo)
{
	if (philo->nbr_of_philos == 1)
	{
		philo->info->died = true;
		print_died(philo);
		return (true);
	}
	pthread_mutex_lock(&philo->info->death_lock);
	if (philo->last_meal + philo->time_to_die <= get_time()
		&& philo->info->died == false)
	{
		philo->info->died = true;
		pthread_mutex_unlock(&philo->info->death_lock);
		print_died(philo);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->death_lock);
	usleep(50);
	return (false);
}

void	check_philo_full(t_philos *philo)
{
	if (philo->meals_eaten == philo->nbr_of_meals)
		philo->state = FINISHED;
}

bool	check_all_full(t_philos *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nbr_of_philos)
	{
		pthread_mutex_lock(&philo->info->state_lock);
		if (philo->info->philos[i].state != FINISHED)
		{
			pthread_mutex_unlock(&philo->info->state_lock);
			return (false);
		}
		pthread_mutex_unlock(&philo->info->state_lock);
	}
	return (true);
}
