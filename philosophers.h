#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <time.h>
# include <unistd.h>
# include <errno.h>
# include <sys/time.h>

# define NICE_PRINT 0

typedef struct s_rules
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
}	t_rules;

typedef struct s_philo
{
	int				first_fork;
	int				second_fork;
	int				id;
	long			timetime;
	int				meals_to_eat;
	t_rules			rules;
	struct s_data	*data;	
}	t_philo;

typedef struct s_data
{
	int				end;
	int				dead_philo;
	long long		time;
	t_philo			*philo;
	t_rules			global_rules;
	pthread_mutex_t	write;
	pthread_mutex_t	mutex_check;
	pthread_mutex_t	*forks;
	pthread_t		*thread_ids;
}	t_data;

// parsing //
int		check_arg(int argc, char **argv);
int		rules_parsing(t_rules *rules);

// init //
int		malloc_data(t_data *data);
int		mutex_init(t_data *data);
void	philo_init(t_data *data, char **argv);
int		philos_and_rules_init(t_data *data, char **argv);
int		init_threads(t_data *data);

// routine //
void	eating(t_philo *philo, int first_fork, int second_fork);
void	forks_init(t_philo *philo);
void	*routine(void *perso);

// utils //
int		ft_atoi(const char *str);
int		clean_mutexes_and_data(t_data *data);
long	get_time(long t0);
void	ft_free(t_data *data);
void	ft_usleep(t_data *data, long time_action);

// philo_life_utils //
int		check_if_continue(t_data *data, t_philo *philo);
void	print_death(t_data *data, int i);
void	check_philo_life(t_data *data);
void	print_meal(t_philo *philo);
void	print_action_and_wait(t_philo *philo, char *action, int time_action);
void	print_routine(t_philo *philo);

#endif
