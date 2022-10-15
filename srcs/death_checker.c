/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:29:42 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/15 19:28:29 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// bool	check_death(t_philos *philo)
// {
// 	if (philo->last_meal + philo->info->time_to_die <= get_time())
// 	{
// 		pthread_mutex_lock(philo->info->death_lock);
// 		philo->info->died = true;
// 		pthread_mutex_unlock(philo->info->death_lock);
// 		print_died(philo);
// 		return (true);
// 	}
// 	return (false);
// }

bool	check_death_state(t_info *info)
{
	pthread_mutex_lock(info->death_lock);
	if (info->died == true)
	{
		pthread_mutex_unlock(info->death_lock);
		return (true);
	}
	pthread_mutex_unlock(info->death_lock);
	return (false);
}

// timestamp() - philo->last_meal >= data()->time_to_die

bool	check_death(t_philos *philo)
{
	pthread_mutex_lock(philo->info->time_lock);
	if ((philo->info->died == false && philo->last_meal + philo->info->time_to_die <= get_time()))
	{
		pthread_mutex_lock(philo->info->death_lock);
		philo->info->died = true;
		pthread_mutex_unlock(philo->info->death_lock);
		print_died(philo);
		pthread_mutex_unlock(philo->info->time_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->info->time_lock);
	return (false);
}


// bool	check_death(t_info *info)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < info->nbr_of_philos)
// 	{
// 		pthread_mutex_lock(info->time_lock);
// 		if ((info->philos[i].last_meal + info->time_to_die <= get_time()) && info->philos[i].state != EATING)
// 		{
// 			pthread_mutex_lock(info->death_lock);
// 			info->died = true;
// 			pthread_mutex_unlock(info->death_lock);
// 			// sleep  a little
// 			print_died(&info->philos[i]);
// 			pthread_mutex_unlock(info->time_lock);
// 			return (true);
// 		}
// 		pthread_mutex_unlock(info->time_lock);
// 	}
// 	return (false);
// }

// void	death_checker(t_info *info)
// {
// 	ft_sleep(info->time_to_die);
// 	while (true)
// 	{
// 		if (check_death(info) == true)
// 			break ;
// 	}
// }

// /**
//  * @brief  sets death bool and prints message
//  * @param  *input: input struct
//  * @param  *philo: philo struct
//  * @param  dead: true if died, false if n_time_eat reached
//  */
// static void	death_routine(t_philo *philo, bool dead)
// {
// 	long	death_time;

// 	pthread_mutex_lock(input->death_lock);
// 	input->death = true;
// 	pthread_mutex_unlock(input->death_lock);
// 	if (dead == true)
// 	{
// 		death_time = get_time() - input->start_time;
// 		ft_sleep(2);
// 		printf(RED"[%ld] %d is dead\n"RESET, death_time, philo->philo_n);
// 	}
// }

// /**
//  * @brief  checks if philo reached death time
//  * @param  *input: input struct
//  * @param  **philos: philo struct
//  * @retval true if dead
//  */
// static bool	check_philo(t_input *input, t_philo **philos)
// {
// 	int		i;

// 	i = 0;
// 	while (philos[i] != NULL)
// 	{
// 		if (input->eat_n_times != -1)
// 			check_eat_status(input, philos[i]);
// 		pthread_mutex_lock(input->time_lock);
// 		if (get_time() - philos[i]->time >= input->time_to_die
// 			&& philos[i]->running == true)
// 		{
// 			pthread_mutex_unlock(input->time_lock);
// 			death_routine(input, philos[i], true);
// 			return (false);
// 		}
// 		pthread_mutex_unlock(input->time_lock);
// 		if (finished_eating(input, philos) == true)
// 		{
// 			death_routine(input, philos[i], false);
// 			return (false);
// 		}
// 		i++;
// 	}
// 	return (true);
// }

// /**
//  * @brief  scans philos for dead people while threads running
//  * @param  *input: input struct
//  * @param  **philos: philo struct
//  */
// void	ft_reaper(t_input *input, t_philo **philos)
// {
// 	input->start_time = get_time();
// 	input->wait = false;
// 	ft_sleep(input->time_to_die - (input->time_to_die / 4));
// 	while (true)
// 	{
// 		if (check_philo(input, philos) == false)
// 			break ;
// 	}
// }