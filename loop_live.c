/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmadison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 03:02:46 by wmadison          #+#    #+#             */
/*   Updated: 2021/07/15 03:02:46 by wmadison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(char *str, t_phi *phi)
{
	pthread_mutex_lock(&phi->all->message);
	printf("%lu %d %s\n", get_time() - phi->all->start, phi->nbr, str);
	pthread_mutex_unlock(&phi->all->message);
}

void	loop_live(void *tmp)
{
	t_phi	*phi;

	phi = (t_phi *)tmp;
	pthread_mutex_lock(phi->left_fork);
	message("has taken a left fork", tmp);
	pthread_mutex_lock(phi->right_fork);
	message("has taken a right fork", tmp);
	message("is eating", tmp);
	usleep(phi->all->time_toeat * 1000);
	pthread_mutex_unlock(phi->right_fork);
	pthread_mutex_unlock(phi->left_fork);
	phi->eaten += 1;
	phi->time_todeath = get_time() + phi->all->time_todie;
	message("is sleeping", tmp);
	usleep(phi->all->time_tosleep * 1000);
	message("is thinking", tmp);
}

void	*checkers(void *tmp)
{
	t_phi	*phi;

	phi = (t_phi *)tmp;
	while (1)
	{
		pthread_mutex_lock(&phi->check);
		if (get_time() > phi->time_todeath)
		{
			pthread_mutex_lock(&phi->all->message);
			printf("%lu %d died\n", get_time() - phi->all->start, phi->nbr);
			pthread_mutex_unlock(&phi->check);
			pthread_mutex_unlock(&phi->all->dead_philo);
			return (NULL);
		}
		pthread_mutex_unlock(&phi->check);
		usleep(1000);
	}
}
