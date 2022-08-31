/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:29:36 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/22 16:02:33 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	is_space(char c)
{
	if (c == ' ')
		return (true);
	return (false);
}

bool	str_of_spaces(char **argv)
{
	int		i;
	int		j;

	i = 0;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j])
		{
			while (is_space(argv[i][j]))
				j++;
			if (argv[i][j] != '\0')
				break ;
			else if (argv[i][j] == '\0')
				return (true);
			j++;
		}
	}
	return (false);
}

void	parser_input_errors(int argc, char **argv)
{
	int		i;
	int		j;

	i = 0;
	if (argc != 5)
		err();
	while (argv[++i])
	{
		if (argv[i][0] == '\0')
			err();
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				if (is_space(argv[i][j]) == false)
					err();
			}
			j++;
		}
	}
	if (str_of_spaces(argv))
		err();
}
