/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acatusse <acatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:09:38 by acatusse          #+#    #+#             */
/*   Updated: 2024/02/23 18:14:31 by acatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Appelée quand un philo meurt, on délock les mutexs pour pouvoir
	écrire et mettre à jour la variable de check.
*/
void	print_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->mutex_check);
	data->dead_philo = 1;
	pthread_mutex_unlock(&data->mutex_check);
	pthread_mutex_lock(&data->write);
	if (NICE_PRINT)
	{
		printf("%ld:	\033[37m \033[35mʚ\033[0mphilo %d\033[35mɞ\033[0m" \
			" \033[31mdied\n\033[ \033[0m", get_time(data->time), i);
	}
	else
		printf("%ld %d died\n", get_time(data->time), i);
	pthread_mutex_unlock(&data->write);
}

/*
	Tourne en boucle jusqu'à ce qu'une condition d'arrêt soit rencontrée.
	Elle fonctionne en bouclant sur l'indice des philosophes de manière
	circulaire.
*/
void	check_philo_life(t_data *data)
{
	int	i;
	int	time_last_meal;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex_check);
		time_last_meal = get_time(data->time) - data->philo[i].timetime;
		pthread_mutex_unlock(&data->mutex_check);
		if (time_last_meal > data->global_rules.time_to_die)
			return (print_death(data, i + 1));
		pthread_mutex_lock(&data->mutex_check);
		if (data->end == 0)
		{
			pthread_mutex_unlock(&data->mutex_check);
			return ;
		}
		pthread_mutex_unlock(&data->mutex_check);
		i++;
		i = i % data->global_rules.nbr_philo;
	}
}

/*
	Vérifie que le programme peut continuer donc qu'aucun philo n'est
	mort de faim ou qu'on arrive pas à la fin de la simulation.
*/
int	check_if_continue(t_data *data, t_philo *philo)
{
	(void)philo;
	pthread_mutex_lock(&data->mutex_check);
	if (data->dead_philo || data->end == 0)
	{
		pthread_mutex_unlock(&data->mutex_check);
		return (-1);
	}
	pthread_mutex_unlock(&data->mutex_check);
	return (1);
}

/*
	On va vérifier si un philo est mort avant d'écrire que le philo mange.
*/
void	print_meal(t_philo *philo)
{
	if (check_if_continue(philo->data, philo) != -1)
	{
		if (NICE_PRINT)
		{
			printf("%ld: 	\033[35mʚ\033[0mphilo %d\033[35mɞ\033[0m has " \
				"taken a fork\n", philo->timetime, philo->id);
			printf("%ld: 	\033[35mʚ\033[0mphilo %d\033[35mɞ\033[0m has " \
				"taken a fork\n", philo->timetime, philo->id);
			printf("%ld: 	\033[35mʚ\033[0mphilo %d\033[35mɞ \033[0m" \
				"\033[32mis eating\n\033[0m", philo->timetime, philo->id);
		}
		else
		{
			printf("%ld %d has taken a fork\n", philo->timetime, philo->id);
			printf("%ld %d has taken a fork\n", philo->timetime, philo->id);
			printf("%ld %d is eating\n", philo->timetime, philo->id);
		}
	}
}

/*
	Utilisé pour écrire dans le terminal les différentes actions des
	philos, il utilise le mutex write pour être sûr qu'ils n'écrivent
	pas tous en même temps.
*/
void	print_action_and_wait(t_philo *philo, char *action, int time_action)
{
	pthread_mutex_lock(&philo->data->write);
	if (check_if_continue(philo->data, philo) != -1
		&& philo->rules.nbr_philo > 1)
	{
		printf(action, get_time(philo->data->time), philo->id);
	}
	pthread_mutex_unlock(&philo->data->write);
	ft_usleep(philo->data, time_action);
}
