/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:07:24 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/20 22:06:00 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_info_1(char **argv, t_info *info)
{
	int		i;

	i = 0;
	while (argv[++i])
	{
		if (i == 1)
			info->nbr_of_philos = ft_atoi_long(argv[i]);
		else if (i == 2)
			info->time_to_die = ft_atoi_long(argv[i]);
		else if (i == 3)
			info->time_to_eat = ft_atoi_long(argv[i]);
		else if (i == 4)
			info->time_to_sleep = ft_atoi_long(argv[i]);
		else if (i == 5)
			info->nbr_of_meals = ft_atoi_long(argv[i]);
	}
}

int	init_info_2(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nbr_of_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (EXIT_FAILURE);
		info->fork_available[i] = true;
	}
	info->died = false;
	return (EXIT_SUCCESS);
}

int	init_mutex(t_info *info)
{
	if (pthread_mutex_init(&info->print_lock, NULL) != 0
		|| pthread_mutex_init(&info->death_lock, NULL) != 0
		|| pthread_mutex_init(&info->time_lock, NULL) != 0
		|| pthread_mutex_init(&info->free_fork_lock, NULL) != 0
		|| pthread_mutex_init(&info->state_lock, NULL) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	init_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nbr_of_philos)
	{
		info->philos[i].philo_id = i + 1;
		info->philos[i].info = info;
		info->philos[i].meals_eaten = 0;
		info->philos[i].time_to_die = info->time_to_die;
		info->philos[i].time_to_eat = info->time_to_eat;
		info->philos[i].time_to_sleep = info->time_to_sleep;
		info->philos[i].nbr_of_meals = info->nbr_of_meals;
		info->philos[i].nbr_of_philos = info->nbr_of_philos;
		init_forks(&info->philos[i], i);
	}
}

int	init(char **argv, t_info *info)
{
	int	i;

	info->nbr_of_meals = -1;
	init_info_1(argv, info);
	if (init_info_2(info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_mutex(info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_philos(info);
	return (EXIT_SUCCESS);
}
