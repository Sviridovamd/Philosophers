/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmadison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 03:03:03 by wmadison          #+#    #+#             */
/*   Updated: 2021/07/15 03:03:03 by wmadison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_structure(t_thinker *thinker)
{
	thinker->philo = -1;
	thinker->time_todie = -1;
	thinker->time_toeat = -1;
	thinker->time_tosleep = -1;
	thinker->many_time_toeat = -1;
}

int	check(t_thinker *thinker)
{
	if ((thinker->time_tosleep < 1) || (thinker->time_toeat < 1)
		|| (thinker->time_todie < 1) || (thinker->philo < 1))
		return (-1);
	return (0);
}

void	fill(t_thinker *thinker, char **argv)
{
	int	i;

	i = 0;
	thinker->philo = ft_atoi(argv[1]);
	thinker->time_todie = ft_atoi(argv[2]);
	thinker->time_toeat = ft_atoi(argv[3]);
	thinker->time_tosleep = ft_atoi(argv[4]);
	thinker->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * thinker->philo);
	while (i < thinker->philo)
	{
		pthread_mutex_init(&thinker->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(thinker->forks, NULL);
	pthread_mutex_init(&thinker->message, NULL);
}

int	fill_thinker(t_thinker *thinker, int argc, char **argv)
{
	if (ft_digits(argv[2]) || ft_digits(argv[2])
		|| ft_digits(argv[3]) || ft_digits(argv[4]))
		return (-1);
	init_structure(thinker);
	fill(thinker, argv);
	if (argc == 6)
	{
		thinker->many_time_toeat = ft_atoi(argv[5]);
		if (thinker->many_time_toeat <= 0)
			return (-1);
	}
	if (check(thinker) != 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_thinker	thinker;

	if (argc < 5 || argc > 6)
	{
		printf("Error: you don't have norm arguments for the game\n");
		return (-1);
	}
	else
	{
		if (fill_thinker(&thinker, argc, argv) != 0)
		{
			printf("Error: you don't have norm arguments for the game\n");
			return (-1);
		}
		thinker.phi = (t_phi *)malloc(sizeof(t_phi) * thinker.philo);
		if (thinker.phi == NULL || thinker.forks == NULL)
			return (-1);
		start_game(&thinker);
	}
	pthread_mutex_lock(&thinker.dead_philo);
	free_clean(&thinker);
	return (0);
}
