/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:49:40 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/18 22:06:49 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_sleep(t_philos *philo)
{
	size_t	start_time;

	philo->state = SLEEPING;
	print_state(philo);
	start_time = get_time();
	while (check_death(philo) == false && philo->info->died == false
		  && start_time + philo->info->time_to_sleep > get_time());
}

void	philo_think(t_philos *philo)
{
	philo->state = THINKING;
	print_state(philo);
}

// void	take_forks(t_philos *philo)
// {
// 	philo->state = PICKING_FORK;
// 	philo->forks_taken = false;
// 	pthread_mutex_lock(philo->l_fork);
// 	print_fork(philo);
// 	pthread_mutex_lock(philo->r_fork);
// 	print_fork(philo);
// 	philo->forks_taken = true;
// }

void	take_l_fork(t_philos *philo)
{
	bool	fork_taken;

	fork_taken = false;
	while (philo->info->died == false && fork_taken == false)
	{
		pthread_mutex_lock(philo->info->free_fork);
		if (*philo->l_fork_free == true)
		{
			pthread_mutex_lock(philo->l_fork);
			*philo->l_fork_free = false;
			print_fork(philo);
			fork_taken = true;
		}
		pthread_mutex_unlock(philo->info->free_fork);
		if (fork_taken == false && check_death(philo) == true)
			break ;
	}
}

void	take_r_fork(t_philos *philo)
{
	bool	fork_taken;

	fork_taken = false;
	while (philo->info->died == false && fork_taken == false)
	{
		pthread_mutex_lock(philo->info->free_fork);
		if (*philo->r_fork_free == true)
		{
			pthread_mutex_lock(philo->r_fork);
			*philo->r_fork_free = false;
			print_fork(philo);
			fork_taken = true;
		}
		pthread_mutex_unlock(philo->info->free_fork);
		if (fork_taken == false && check_death(philo) == true)
			break ;
	}
}

// void	take_forks(t_philos *philo)
// {

// 	pthread_mutex_lock(philo->l_fork);
// 	print_fork(philo);
// 	pthread_mutex_lock(philo->r_fork);
// 	print_fork(philo);
// }

void	take_one_fork(t_philos *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_fork(philo);
}

void	philo_eat(t_philos *philo)
{
	if (philo->info->nbr_of_philos > 1)
	{
		take_l_fork(philo);
		take_r_fork(philo);
	}
	else
		take_one_fork(philo);
	if (philo->info->died == true)
		return ;
	pthread_mutex_lock(philo->info->time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->info->time_lock);
	philo->state = EATING;
	print_state(philo);
	ft_sleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	if (philo->info->nbr_of_philos > 1)
		pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(philo->info->free_fork);
	*philo->r_fork_free = true;
	*philo->l_fork_free = true;
	pthread_mutex_unlock(philo->info->free_fork);
	pthread_mutex_lock(philo->info->eat_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->info->eat_lock);
	check_philo_full(philo);
}
