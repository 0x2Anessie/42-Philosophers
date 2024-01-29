/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acatusse <acatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:06:36 by acatusse          #+#    #+#             */
/*   Updated: 2024/01/05 17:56:18 by acatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @used in main
 * @brief 	Detruit les mutex et libere la memoire qui a ete malloc pour les
 * 			fourchettes, les identifiants de threads et les structures des 
 * 			philo.
 * 
 * @include pthread_mutex_destroy qui renvoie une valeur nulle si le mutex
 * 			est detruit et non nulle si il n'a pas pu l'etre.
 * 
 * @return au main le nombre de mutex qui n'ont pas pu etre detruits.
 */
int	clean_mutexes_and_data(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < data->global_rules.nbr_philo)
	{
		if (pthread_mutex_destroy(&data->forks[i]))
			j++;
		i++;
	}
	if (pthread_mutex_destroy(&data->mutex_check))
		j++;
	if (pthread_mutex_destroy(&data->write))
		j++;
	if (data->forks)
		free(data->forks);
	if (data->thread_ids)
		free(data->thread_ids);
	if (data->philo)
		free(data->philo);
	return (j);
}

int	ft_init_and_start(t_data *data)
{
	int	i;

	i = 0;
	data->t0 = get_time(0);
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

/**
 * @brief 	 
 * 
 * @include check_arg qui verifie la validite des arguments.
 * 
 * @include ft_init initialise les regles avec les arguments, alloue la memoire
 * 			pour fork, thread_ids et philo puis initialise les mutex et les
 * 			philosophes.
 * 
 * @include	ft_init_and_start 
 * 
 * @return 	le nombre de mutex non detruits.
 */
int	main(int argc, char **argv)
{
	t_data	data;
	int		error;

	data.someone_died = 0;
	error = 0;
	if (argc < 5 || argc > 6)
		return (printf("\033[31mWrong number of arguments !\n\033["));
	if (check_arg(argc, argv) == 1)
		return (-1);
	if (ft_init(&data, argv) == -1)
		return (-1);
	error = ft_init_and_start(&data);
	if (error == 1)
		printf("\033[31mProblem creating threads !\n\033[");
	else if (error == 2)
		printf("\033[31mProblem joining threads !\n\033[");
	return (clean_mutexes_and_data(&data)); // POURQQUOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOIII???
}
