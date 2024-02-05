/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acatusse <acatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:06:13 by acatusse          #+#    #+#             */
/*   Updated: 2024/02/05 15:34:05 by acatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Free les variables philo, threads_ids et forks dans le cas où leur malloc
	dans init_malloc à echoué.
*/
void	ft_free(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->thread_ids)
		free(data->thread_ids);
	if (data->forks)
		free(data->forks);
}

/*
	Alloue la mémoire pour les philosophes, leurs identifiants de thread, et
	les mutexes pour les fourchettes. Retourne 1 en cas d'échec d'allocation
	et libère ce qui à déjà été alloué.
*/
int	init_malloc(t_data *data)
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
	Pour chaque philo, on lui assigne de la data, sa position, le temps,
	les règles passées en argument et le nombre de repas qu'il leur reste
	à manger.
*/
void	init_phi(t_data *data, char **argv)
{
	int	i;

	i = 0;
	while (i < data->global_rules.nbr_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].time = 0;
		data->philo[i].rules = data->global_rules;
		if (argv[5])
			data->philo[i].meals_to_eat = ft_atoi(argv[5]);
		else
			data->philo[i].meals_to_eat = -1;
		i++;
	}
}

/*
	Initialise tous les mutexes nécessaires pour le programme. C'est a dire
	un mutex par fourchette(forks), un pour écrire dans le terminal pour 
	qu'ils écrivent(write) pas tous en même temps, et un pour vérifier des
	données comme si ils ont mangés tous leurs plats ou si l'un est mort.
*/
int	init_mutex(t_data *data)
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
	Initialise les règles avec les arguments et crée time_to_think qui occupe
	le temps ou les philos ne dorment ou ne mangent pas, c'est a dire
*/
int	philos_and_rules_init(t_data *data, char **argv)
{
	t_rules	rules;

	rules.nbr_philo = ft_atoi(argv[1]);
	rules.time_to_die = ft_atoi(argv[2]) - 1;
	rules.time_to_eat = ft_atoi(argv[3]);
	rules.time_to_sleep = ft_atoi(argv[4]);
	rules.time_to_think = (rules.time_to_die - rules.time_to_eat
			- rules.time_to_sleep) * 0.75;
	data->global_rules = rules;
	if (rules.nbr_philo <= 0 || rules.time_to_die <= 0 || rules.time_to_eat <= 0
		|| rules.time_to_sleep <= 0)
		return (printf("\033[31mWrong arguments !\n\033["), -1);
	data->fini = rules.nbr_philo;
	if (init_malloc(data) == 1)
		return (printf("\033[31mAllocation problem !\n\033["), -1);
	if (init_mutex(data) == 1)
		return (ft_free(data), -1);
	return (init_phi(data, argv), 1);
}
