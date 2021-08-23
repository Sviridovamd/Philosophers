#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <inttypes.h>

typedef struct s_thinker
{
	int				philo;
	struct s_phi	*phi;
	uint64_t		start;
	uint64_t		time_toeat;
	uint64_t		time_tosleep;
	int				many_time_toeat;
	uint64_t		time_todie;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_philo;
	pthread_mutex_t	message;
}	t_thinker;

typedef struct s_phi
{
	int				how_dead;
	int				even;
	int				eaten;
	int				nbr;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	uint64_t		last_eat;
	uint64_t		time_todeath;
	pthread_t		thread;
	pthread_mutex_t	check;
	t_thinker		*all;
}	t_phi;

int			ft_atoi(const char *str);
int			ft_digits(char *str);
void		start_game(t_thinker *thinker);
uint64_t	get_time(void);
void		message(char *str, t_phi *phi);
void		loop_live(void *tmp);
void		*checkers(void *tmp);
void		free_clean(t_thinker *thinker);

#endif
