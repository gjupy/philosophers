/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:49:40 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/20 14:06:41 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_sleep(t_philos *philo)
{
	size_t	current_time;

	// pthread_mutex_lock(philo->info->time_lock);
	if (philo->info->died == false)
	{
		philo->state = SLEEPING;
 		print_state(philo);
		current_time = get_time() + philo->info->time_to_sleep;
		while (current_time > get_time() && philo->info->died == false)
		{
			// pthread_mutex_unlock(philo->info->time_lock);
			usleep(50);
			if (check_death(philo) == true)
				break ;
			// pthread_mutex_lock(philo->info->time_lock);
		}
	}
	// pthread_mutex_unlock(philo->info->time_lock);
}

void	philo_think(t_philos *philo)
{
	if (philo->info->died == false)
	{
		philo->state = THINKING;
		print_state(philo);
	}
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

// void	take_r_fork(t_philos *philo)
// {
// 	bool	fork_taken;

// 	fork_taken = false;
// 	while (philo->info->died == false && fork_taken == false)
// 	{
// 		pthread_mutex_lock(philo->info->free_fork);
// 		if (*philo->r_fork_free == true)
// 		{
// 			pthread_mutex_lock(philo->r_fork);
// 			*philo->r_fork_free = false;
// 			print_fork(philo);
// 			fork_taken = true;
// 		}
// 		pthread_mutex_unlock(philo->info->free_fork);
// 		if (fork_taken == false && check_death(philo) == true)
// 			break ;
// 	}
// }

// void	take_l_fork(t_philos *philo)
// {
// 	bool	fork_taken;

// 	fork_taken = false;
// 	while (philo->info->died == false && fork_taken == false)
// 	{
// 		pthread_mutex_lock(philo->info->free_fork);
// 		if (*philo->l_fork_free == true)
// 		{
// 			pthread_mutex_lock(philo->l_fork);
// 			*philo->l_fork_free = false;
// 			print_fork(philo);
// 			fork_taken = true;
// 		}
// 		pthread_mutex_unlock(philo->info->free_fork);
// 		if (fork_taken == false && check_death(philo) == true)
// 			break ;
// 	}
// }

// void	take_forks(t_philos *philo)
// {

// 	pthread_mutex_lock(philo->r_fork);
// 	print_fork(philo);
// 	pthread_mutex_lock(philo->l_fork);
// 	print_fork(philo);
// }

void	take_forks(t_philos *philo)
{
	int	forks;

	forks = FREE;
	while (philo->info->died == false && forks != TAKEN)
	{
		pthread_mutex_lock(philo->info->free_fork);
		if (*philo->l_fork_free == true)
		{
			pthread_mutex_lock(philo->l_fork);
			*philo->l_fork_free = false;
			print_fork(philo);
			forks++;
		}
		pthread_mutex_unlock(philo->info->free_fork);
		pthread_mutex_lock(philo->info->free_fork);
		if (*philo->r_fork_free == true)
		{
			pthread_mutex_lock(philo->r_fork);
			*philo->r_fork_free = false;
			print_fork(philo);
			forks++;
		}
		pthread_mutex_unlock(philo->info->free_fork);
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
	if (philo->info->nbr_of_philos > 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_lock(philo->info->free_fork);
		*philo->r_fork_free = true;
		pthread_mutex_unlock(philo->info->free_fork);
		pthread_mutex_lock(philo->info->free_fork);
		*philo->l_fork_free = true;
		pthread_mutex_unlock(philo->info->free_fork);
	}
}

bool	ft_eating(t_philos *philo)
{
	size_t	current_time;

	current_time = get_time() + philo->info->time_to_eat;
	while (current_time > get_time() && philo->info->died == false)
	{
		// pthread_mutex_unlock(philo->info->time_lock);
		usleep(50);
		if (check_death(philo) == true)
			return (false) ;
		// pthread_mutex_lock(philo->info->time_lock);
	}
	return (true);
}

void	philo_eat(t_philos *philo)
{
	if (philo->info->nbr_of_philos > 1)
		take_forks(philo);
	else
		take_one_fork(philo);
	// pthread_mutex_lock(philo->info->death_lock);
	if (philo->info->died == true)
	{
		// pthread_mutex_unlock(philo->info->death_lock);
		return ;
	}
	// pthread_mutex_unlock(philo->info->death_lock);
	philo->last_meal = get_time();
	philo->state = EATING;
	print_state(philo);
	// ft_sleep(philo->info->time_to_eat);
	if (ft_eating(philo) == true)
	{
		return_forks(philo);
		philo->meals_eaten++;
		check_philo_full(philo);
	}
}
