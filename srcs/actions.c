/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:49:40 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/20 21:37:51 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_sleep(t_philos *philo)
{
	size_t	current_time;

	if (check_death_state(philo->info) == false)
	{
		philo->state = SLEEPING;
		print_state(philo);
		current_time = get_time() + philo->time_to_sleep;
		while (current_time > get_time()
			&& check_death_state(philo->info) == false)
		{
			usleep(50);
			if (check_death(philo) == true)
				break ;
		}
	}
}

void	philo_think(t_philos *philo)
{
	if (check_death_state(philo->info) == false)
	{
		philo->state = THINKING;
		print_state(philo);
	}
}

bool	ft_eating(t_philos *philo)
{
	size_t	current_time;

	current_time = get_time() + philo->time_to_eat;
	while (current_time > get_time() && check_death_state(philo->info) == false)
	{
		usleep(50);
		if (check_death(philo) == true)
			return (false);
	}
	return (true);
}

void	philo_eat(t_philos *philo)
{
	if (philo->info->nbr_of_philos > 1)
		take_forks(philo);
	else
		take_one_fork(philo);
	philo->last_meal = get_time();
	if (check_death_state(philo->info) == true)
		return ;
	philo->state = EATING;
	print_state(philo);
	if (ft_eating(philo) == true)
	{
		return_forks(philo);
		philo->meals_eaten++;
		check_philo_full(philo);
	}
}
