/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 21:27:26 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/20 21:41:56 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_l_fork(t_philos *philo, int *forks)
{
	pthread_mutex_lock(&philo->info->free_fork_lock);
	if (*philo->l_fork_free == true)
	{
		pthread_mutex_lock(philo->l_fork);
		*philo->l_fork_free = false;
		print_fork(philo);
		(*forks)++;
	}
	pthread_mutex_unlock(&philo->info->free_fork_lock);
}

void	take_r_fork(t_philos *philo, int *forks)
{
	pthread_mutex_lock(&philo->info->free_fork_lock);
	if (*philo->r_fork_free == true)
	{
		pthread_mutex_lock(philo->r_fork);
		*philo->r_fork_free = false;
		print_fork(philo);
		(*forks)++;
	}
	pthread_mutex_unlock(&philo->info->free_fork_lock);
}

void	take_forks(t_philos *philo)
{
	int	forks;

	forks = FREE;
	while (forks != TAKEN && check_death_state(philo->info) == false)
	{
		take_l_fork(philo, &forks);
		take_r_fork(philo, &forks);
		if (forks != TAKEN && check_death(philo) == true)
			break ;
	}
}

void	take_one_fork(t_philos *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_fork(philo);
}

void	return_forks(t_philos *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	if (philo->nbr_of_philos > 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_lock(&philo->info->free_fork_lock);
		*philo->r_fork_free = true;
		pthread_mutex_unlock(&philo->info->free_fork_lock);
		pthread_mutex_lock(&philo->info->free_fork_lock);
		*philo->l_fork_free = true;
		pthread_mutex_unlock(&philo->info->free_fork_lock);
	}
}
