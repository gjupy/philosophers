/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:49:40 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/31 12:20:14 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_sleep(t_philos *philo)
{
	size_t	start_time;

	philo->state = SLEEPING;
	print_state(philo);
	start_time = get_time();
	while (start_time + philo->info->time_to_sleep > get_time());
	philo->state = THINKING;
	if (check_death_state(philo->info) == false)
		print_state(philo);
}

void	take_fork(t_philos *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_fork(philo);
	pthread_mutex_lock(philo->r_fork);
	print_fork(philo);
}

void	philo_eat(t_philos *philo)
{
	size_t	start_time;

	take_fork(philo);
	pthread_mutex_lock(philo->info->time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->info->time_lock);
	philo->state = EATING;
	print_state(philo);
	start_time = get_time();
	while (start_time + philo->info->time_to_eat > get_time());
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
