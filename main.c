#include "philosophers.h"

void	print_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (NICE_PRINT)
		{
			print_action_and_wait(philo, "%ld: 	\033[35mʚ\033[0mphilo %d\033[35mɞ"
				"\033[0m is thinking\n", philo->rules.time_to_think);
		}
		else
			print_action_and_wait(philo, "%ld %d is thinking\n", \
				philo->rules.time_to_think);
	}
	else if (philo->id == philo->rules.nbr_philo)
	{
		if (NICE_PRINT)
		{
			print_action_and_wait(philo, "%ld: 	\033[35mʚ\033[0mphilo %d\033[35mɞ"
				"\033[0m is thinking\n", philo->rules.time_to_eat);
		}
		else
			print_action_and_wait(philo, "%ld %d is thinking\n", \
				philo->rules.time_to_eat);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		error;

	data.dead_philo = 0;
	error = 0;
	if (argc < 5 || argc > 6)
		return (printf("\033[31mWrong number of arguments !\n\033["));
	if (check_arg(argc, argv) == 1)
		return (-1);
	if (philos_and_rules_init(&data, argv) == -1)
		return (-1);
	error = init_threads(&data);
	if (error == 1)
		printf("\033[31mProblem creating threads !\n\033[");
	else if (error == 2)
		printf("\033[31mProblem ending threads !\n\033[");
	return (clean_mutexes_and_data(&data));
}
