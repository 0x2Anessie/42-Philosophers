/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acatusse <acatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:06:45 by acatusse          #+#    #+#             */
/*   Updated: 2024/02/05 15:25:05 by acatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <time.h>
# include <unistd.h>
# include <errno.h>
# include <sys/time.h>

typedef struct s_rules
{
	int	nbr_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_think;
}	t_rules;

typedef struct s_philo
{
	int				first_fork;
	int				second_fork;
	int				id;
	long			time;
	int				meals_to_eat;
	t_rules			rules;
	struct s_data	*data;	
}	t_philo;

typedef struct s_data
{
	long long		t0;
	int				fini;
	int				someone_died;
	pthread_mutex_t	mutex_check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_t		*thread_ids;
	t_philo			*philo;
	t_rules			global_rules;
}	t_data;

int		philos_and_rules_init(t_data *data, char **argv);

long	get_time(long t0);
int		ft_atoi(const char *nptr);
int		check_philo_continue(t_data *data, t_philo *philo);
void	print_meal(t_philo *philo);
void	ft_usleep(t_data *data, long time_action);

void	*routine(void *perso);

void	check_philo_life(t_data *data);
int		check_arg(int argc, char **argv);

#endif