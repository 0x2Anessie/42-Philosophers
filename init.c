#include "philosophers.h"

/*
	Alloue pour chaque philo de la mémoire pour toutes les data de la
	structure t_philo, pour un thread par philo et pour un mutex par fourchette.
*/
int	malloc_data(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->global_rules.nbr_philo);
	if (!data->philo)
		return (1);
	data->thread_ids = malloc(sizeof(pthread_t) * data->global_rules.nbr_philo);
	if (!data->philo)
		return (free(data->philo), 1);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->global_rules.nbr_philo);
	if (!data->forks)
		return (free(data->philo), free(data->thread_ids), 1);
	return (0);
}

/*
	Initialise le mutex pour écrire dans le terminal (write) et celui pour
	effectuer des vérifications pendant le programme (mutex check).
	Puis pour chaque nombre de philo on va créer un mutex par fourchette.
*/
int	mutex_init(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->write, NULL))
		return (1);
	if (pthread_mutex_init(&data->mutex_check, NULL))
		return (pthread_mutex_destroy(&data->write), 1);
	i = 0;
	while (i < data->global_rules.nbr_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (i-- >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			return (pthread_mutex_destroy(&data->write),
				pthread_mutex_destroy(&data->mutex_check), 1);
		}
		i++;
	}
	return (0);
}

/*
	Pour chaque philo on initialise les données nécessaire pour
	qu'il soit utilisé dans le reste du programme.
*/
void	philo_init(t_data *data, char **argv)
{
	int	i;

	i = 0;
	while (i < data->global_rules.nbr_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].timetime = 0;
		data->philo[i].rules = data->global_rules;
		if (argv[5])
			data->philo[i].meals_to_eat = ft_atoi(argv[5]);
		else
			data->philo[i].meals_to_eat = -1;
		i++;
	}
}

/*
	Initialise les règles globales du programme avec les arguments, vérifie
	leurs validités, si c'est ok, alloue de la mémoire pour les data
	nécessaires au programme.
*/
int	philos_and_rules_init(t_data *data, char **argv)
{
	t_rules	rules;

	rules.nbr_philo = ft_atoi(argv[1]);
	rules.time_to_die = ft_atoi(argv[2]) - 1;
	rules.time_to_eat = ft_atoi(argv[3]);
	rules.time_to_sleep = ft_atoi(argv[4]);
	rules.time_to_think = (rules.time_to_die - rules.time_to_eat \
							- rules.time_to_sleep) * 0.75;
	data->global_rules = rules;
	if (rules_parsing(&rules) == 1)
		return (-1);
	data->end = rules.nbr_philo;
	if (malloc_data(data) == 1)
		return (printf("\033[31mAllocation problem !\n\033["), -1);
	if (mutex_init(data) == 1)
		return (ft_free(data), -1);
	return (philo_init(data, argv), 1);
}

/*
	On boucle d'abord sur chaque philo pour lui initialiser un thread, si
	l'init échoue,on entre dans une boucle pour attendre la fin de tous les
	threads déjà créés, puis on sort de la fonction.
	On initialise une boucle qui tournera en boucle pour vérifier si
	un philo meurt ou qu'on arrive a la fin du programme
*/
int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->time = get_time(0);
	while (i < data->global_rules.nbr_philo)
	{
		if (pthread_create(&data->thread_ids[i], NULL, &routine,
				&data->philo[i]))
		{
			while (i-- >= 0)
				pthread_join(data->thread_ids[i], NULL);
			return (1);
		}
		i++;
	}
	check_philo_life(data);
	i = 0;
	while (i < data->global_rules.nbr_philo)
	{
		if (pthread_join(data->thread_ids[i], NULL))
			return (2);
		i++;
	}
	return (0);
}
