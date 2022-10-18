void	return_forks(t_philo *philo, t_philo *neighbour)
{
	pthread_mutex_lock(&neighbour->fork);
	neighbour->fork_free = true;
	pthread_mutex_unlock(&neighbour->fork);
	pthread_mutex_lock(&philo->fork);
	philo->fork_free = true;
	pthread_mutex_unlock(&philo->fork);
}

void	take_one_fork(t_philo *philo)
{
	bool	fork_taken;

	fork_taken = false;
	while (!fork_taken && data()->all_alive)
	{
		pthread_mutex_lock(&philo->fork);
		if (philo->fork_free)
		{
			philo->fork_free = false;
			fork_taken = true;
		}
		pthread_mutex_unlock(&philo->fork);
		usleep(50);
		if (check_philo_starving(philo))
			break ;
	}
}

void	philo_eats(t_philo *philo)
{
	if (data()->all_alive)
	{
		take_one_fork(philo);
		print_act(philo->id, "has taken a fork.");
		take_one_fork(data()->philos[philo->next_id]);
		print_act(philo->id, "has taken a fork.");
		if (!data()->all_alive)
			return ;
		philo->meals++;
		philo->last_meal = timestamp();
		print_act(philo->id, "is eating.");
		ft_usleep(data()->time_to_eat);
		return_forks(philo, data()->philos[philo->next_id]);
		switch_status(philo->id, waiting);
	}
}