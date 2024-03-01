/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acatusse <acatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:17:27 by acatusse          #+#    #+#             */
/*   Updated: 2024/02/23 18:14:31 by acatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Si le philo a bien les deux fourchettes en main, on le fait manger en
	actualisant l'heure de son dernier repas, en écrivant qu'il a pris ses
	fourchettes et qu'il mange. On actualise le nombre de repas et
	on libère les mutexs des fourchettes.
*/
void	eating(t_philo *philo, int first_fork, int second_fork)
{
	if (!pthread_mutex_lock(&philo->data->forks[first_fork])
		&& !pthread_mutex_lock(&philo->data->forks[second_fork]))
	{
		pthread_mutex_lock(&philo->data->mutex_check);
		philo->timetime = get_time(philo->data->time);
		pthread_mutex_unlock(&philo->data->mutex_check);
		pthread_mutex_lock(&philo->data->write);
		print_meal(philo);
		pthread_mutex_unlock(&philo->data->write);
		ft_usleep(philo->data, philo->rules.time_to_eat);
		pthread_mutex_lock(&philo->data->mutex_check);
		philo->meals_to_eat--;
		if (philo->meals_to_eat == 0)
			philo->data->end--;
		pthread_mutex_unlock(&philo->data->mutex_check);
	}
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
}

/*
	On vérifie si il n'y a pas qu'un seul philo, et on définie la position
	des fourchettes selon si le philo a une position paire ou impaire.
	Cela permet de mettre les philos à une table ronde, c'est à dire
	que l'une des fourchettes du dernier philo sera à l'indice 0.
*/
void	forks_init(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	first_fork = 0;
	second_fork = 0;
	if (philo->rules.nbr_philo == 1)
		return ;
	if (philo->id % 2 == 0)
	{
		first_fork = philo->id - 1;
		second_fork = philo->id % philo->rules.nbr_philo;
	}
	else if (philo->id % 2 != 0)
	{
		first_fork = philo->id % philo->rules.nbr_philo;
		second_fork = philo->id - 1;
	}
	eating(philo, first_fork, second_fork);
}

/*
	On traite si le philo a une position paire ou impaire, en fonction
	on le fait soit manger en premier soit penser. Puis dans une boucle
	infinie on le fait manger, dormir et penser.
*/
void	*routine(void *perso)
{
	t_philo	*philo;

	philo = (t_philo *) perso;
	print_routine(philo);
	while (1)
	{
		forks_init(philo);
		if (NICE_PRINT)
		{
			print_action_and_wait(philo, "%ld: 	\033[35mʚ\033[0mphilo %d\033[35mɞ"
				"\033[0m is sleeping\n", philo->rules.time_to_sleep);
			print_action_and_wait(philo, "%ld: 	\033[35mʚ\033[0mphilo %d\033[35mɞ"
				"\033[0m is thinking\n", philo->rules.time_to_think);
		}
		else
		{
			print_action_and_wait(philo, "%ld %d"
				" is sleeping\n", philo->rules.time_to_sleep);
			print_action_and_wait(philo, "%ld %d"
				" is thinking\n", philo->rules.time_to_think);
		}
		if (check_if_continue(philo->data, philo) == -1)
			return ((void *) 0);
	}
}
