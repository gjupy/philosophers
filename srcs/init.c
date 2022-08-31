/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:07:24 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/31 15:26:42 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_info(char **argv, t_info *info)
{
	int		i;
	int		j;
	char	**s;

	i = 0;
	while (argv[++i])
	{
		s = ft_split(argv[i], ' ');
		if (s == NULL)
			malloc_err();
		j = -1;
		while (s[++j])
		{
			if (i == 1)
		 		info->nbr_of_philos = ft_atoi_long(s[j]);
			else if (i == 2)
				info->time_to_die = ft_atoi_long(s[j]);
			else if (i == 3)
				info->time_to_eat = ft_atoi_long(s[j]);
			else if (i == 4)
				info->time_to_sleep = ft_atoi_long(s[j]);
			free(s[j]);
		}
		free(s);
	}
}

void	init_mutex(t_info *info)
{
	info->print_lock = malloc(sizeof(pthread_mutex_t));
	info->death_lock = malloc(sizeof(pthread_mutex_t));
	info->time_lock = malloc(sizeof(pthread_mutex_t));
	info->eat_lock = malloc(sizeof(pthread_mutex_t));
	if (info->print_lock == NULL || info->death_lock == NULL
		|| info->time_lock == NULL || info->eat_lock == NULL)
		malloc_err();
	if (pthread_mutex_init(info->print_lock, NULL) != 0 ||
	pthread_mutex_init(info->death_lock, NULL) != 0 ||
	pthread_mutex_init(info->time_lock, NULL) != 0 ||
	pthread_mutex_init(info->eat_lock, NULL) != 0)
		err();
}

void	init_forks(t_philos *philo, int i)
{
	philo->l_fork = malloc(sizeof(pthread_mutex_t));
	philo->r_fork = malloc(sizeof(pthread_mutex_t));
	if (philo->l_fork == NULL || philo->r_fork == NULL)
		malloc_err();
	pthread_mutex_init(philo->l_fork, NULL);
	pthread_mutex_init(philo->r_fork, NULL);
	philo->r_fork = &philo->info->forks[i];
	philo->l_fork = &philo->info->forks[(i + 1) % philo->info->nbr_of_philos];
}

void	init_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nbr_of_philos)
	{
		info->philos[i].philo_id = i + 1;
		info->philos[i].info = info;
		info->philos[i].last_meal = 0;
		init_forks(&info->philos[i], i);
	}
}

void	init(char **argv, t_info *info)
{
	init_info(argv, info);
	info->died = false;
	pthread_mutex_init(info->forks, NULL);
	init_mutex(info);
	init_philos(info);
	// int i = -1;
	// while (++i < info->nbr_of_philos)
	// {
	// 	printf("philo %d\nleft: %lu right %d\n", info->philos[i].philo_id, (i + 1) % info->nbr_of_philos, i);
	// }
}
