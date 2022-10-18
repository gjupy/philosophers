/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:57:07 by gjupy             #+#    #+#             */
/*   Updated: 2022/10/18 20:27:26 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define PHILO_MAX 200
# define PURPLE "\033[0;35m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

typedef enum		e_state
{
	EATING,
	SLEEPING,
	THINKING,
	RUNNING,
	FINISHED,
	PICKING_FORK
}					t_state;

struct s_info;

typedef struct s_philos
{
	int				philo_id;
	int				fork;
	int				meals_eaten;
	int				array_index;
	int				array_index_l;
	int				array_index_r;
	time_t			last_meal;
	// size_t			limit;
	time_t			start_time;
	t_state			state;
	struct s_info	*info;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		t_id;
	bool			forks_taken;
	// bool			r_fork_free;
	// bool			l_fork_free;
	bool			*r_fork_free;
	bool			*l_fork_free;
}	t_philos;

typedef struct s_info
{
	int			nbr_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nbr_of_meals;
	bool			died;
	bool			wait;
	time_t			start;
	t_state			state;
	pthread_mutex_t	forks[PHILO_MAX];
	t_philos 		philos[PHILO_MAX];
	bool			fork_available[PHILO_MAX];
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*time_lock;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*free_fork;
	pthread_mutex_t	*eat_lock;
}	t_info;

void	parser_input_errors(int argc, char **argv);
void	err(void);
void	malloc_err(void);
void	init(char **argv, t_info *info);
void	start_threads(t_info *info);
time_t	get_time(void);

void	philo_sleep(t_philos *philo);
void	philo_eat(t_philos *philo);
void	philo_think(t_philos *philo);

void	print_state(t_philos *philo);
void	print_fork(t_philos *philo);
void	print_died(t_philos *philo);

void	death_checker(t_info *info);

void	free_all(t_info *info);

// bool	check_death(t_info *info);
bool	check_death(t_philos *philo);
bool	check_death_state(t_info *info);
void	check_death_eating(t_info *info);
void	check_philo_full(t_philos *philo);
bool	check_all_full(t_info *info);

void	ft_sleep(time_t time);

#endif
