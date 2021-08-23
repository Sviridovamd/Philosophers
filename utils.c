/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmadison <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 03:03:15 by wmadison          #+#    #+#             */
/*   Updated: 2021/07/15 03:03:15 by wmadison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_clean(t_thinker *thinker)
{
	int	i;

	pthread_mutex_destroy(&thinker->dead_philo);
	pthread_mutex_destroy(&thinker->message);
	i = 0;
	while (i < thinker->philo)
	{
		pthread_mutex_destroy(&thinker->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&thinker->dead_philo);
	free(thinker->forks);
	free(thinker->phi);
}

int	ft_digits(char *str)
{
	int	f;
	int	i;

	f = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			f = 1;
		i++;
	}
	return (f);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	num;

	i = 0;
	n = 1;
	num = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9' && str[i] != '\0')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * n);
}

uint64_t	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (uint64_t)1000) + time.tv_usec / 1000);
}
