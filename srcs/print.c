/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:26:39 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/20 18:52:30 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_state(t_philos *philo)
{
	size_t	current_time;
	size_t	new_time;

	new_time = get_time();
	current_time = new_time - philo->start_time;
	pthread_mutex_lock(&philo->info->print_lock);
	if (philo->state == SLEEPING)
		printf("%ld %d is sleeping\n", current_time, philo->philo_id);
	else if (philo->state == EATING)
		printf(GREEN"%ld %d is eating\n"RESET, current_time, philo->philo_id);
	else if (philo->state == THINKING)
		printf("%ld %d is thinking\n", current_time, philo->philo_id);
	pthread_mutex_unlock(&philo->info->print_lock);
}

void	print_fork(t_philos *philo)
{
	size_t	current_time;
	size_t	new_time;

	new_time = get_time();
	current_time = new_time - philo->start_time;
	pthread_mutex_lock(&philo->info->print_lock);
	printf("%ld %d has taken a fork\n", current_time, philo->philo_id);
	pthread_mutex_unlock(&philo->info->print_lock);
}

void	print_died(t_philos *philo)
{
	size_t	current_time;
	size_t	new_time;

	new_time = get_time();
	current_time = new_time - philo->start_time;
	pthread_mutex_lock(&philo->info->print_lock);
	printf(PURPLE"%ld %d died\n"RESET, current_time, philo->philo_id);
	pthread_mutex_unlock(&philo->info->print_lock);
}
