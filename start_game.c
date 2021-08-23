/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmadison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 03:03:26 by wmadison          #+#    #+#             */
/*   Updated: 2021/07/15 03:03:26 by wmadison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*live(void *tmp)
{
	pthread_t	tred;
	t_phi		*phi;

	phi = (t_phi *)tmp;
	if (phi->even)
	{
		usleep(1000);
		phi->even = 0;
	}
	phi->last_eat = get_time();
	phi->time_todeath = phi->last_eat + phi->all->time_todie;
	if (pthread_create(&tred, NULL, &checkers, phi) != 0)
		return ((void *)1);
	pthread_detach(tred);
	while (phi->eaten != phi->all->many_time_toeat)
		loop_live(phi);
	usleep(1000);
	pthread_mutex_lock(&phi->all->message);
	pthread_mutex_unlock(&phi->all->dead_philo);
	return (NULL);
}

void	*check_live(void *tmp)
{
	t_thinker	*thinker;
	int			i;

	thinker = (t_thinker *)tmp;
	while (1)
	{
		i = 0;
		while (i < thinker->philo)
		{
			if (thinker->phi[i].eaten < thinker->many_time_toeat)
				break ;
			i++;
		}
		if (i == thinker->philo)
			break ;
		usleep(1000);
	}
	pthread_mutex_lock(&thinker->message);
	pthread_mutex_unlock(&thinker->dead_philo);
	return (NULL);
}

int	start_pthread(t_thinker *thinker)
{
	int			i;
	pthread_t	tred;

	thinker->start = get_time();
	if (thinker->many_time_toeat != -1)
	{
		if (pthread_create(&tred, NULL, &check_live, thinker) != 0)
			return (1);
	}
	i = 0;
	while (i < thinker->philo)
	{
		thinker->phi[i].time_todeath = get_time() + thinker->time_todie;
		if (pthread_create(&thinker->phi[i].thread, NULL, &live,
				(void *)(&thinker->phi[i])) != 0)
			return (-1);
		pthread_detach(thinker->phi[i].thread);
		i++;
	}
	return (0);
}

void	make_start(t_thinker *thinker)
{
	int	i;

	i = 0;
	while (i < thinker->philo)
	{
		pthread_mutex_init(&thinker->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&thinker->message, NULL);
	pthread_mutex_init(&thinker->dead_philo, NULL);
	pthread_mutex_lock(&thinker->dead_philo);
}

void	start_game(t_thinker *thinker)
{
	int	i;

	i = 0;
	while (i < thinker->philo)
	{
		thinker->phi[i].last_eat = 0;
		thinker->phi[i].how_dead = 0;
		thinker->phi[i].eaten = 0;
		thinker->phi[i].nbr = i + 1;
		thinker->phi[i].even = 0;
		if ((thinker->phi[i].nbr % 2) == 0)
			thinker->phi[i].even = 1;
		thinker->phi[i].left_fork = &thinker->forks[i];
		thinker->phi[i].right_fork = &thinker->forks[(i + 1) % thinker->philo];
		thinker->phi[i].all = thinker;
		i++;
	}
	make_start(thinker);
	start_pthread(thinker);
}
