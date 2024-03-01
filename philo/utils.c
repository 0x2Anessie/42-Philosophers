/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acatusse <acatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:17:32 by acatusse          #+#    #+#             */
/*   Updated: 2024/02/27 12:51:16 by acatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Atoi basique mais gere le INT_MIN et INT_MAX ce qui aide au parsing parce
	que le -1 passera pas parse_rules.
*/
int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((str[i] >= '\t' && str[i] <= '\r')
		|| str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if ((sign * nb) < INT_MIN || (sign * nb) > INT_MAX)
		return (-1);
	return ((int)sign * nb);
}

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
	En fin de programme elle détruit les mutexs et free la mémoire allouée
	aux données. Elle return le nombre de mutexs qu'elle n'a pas réussi
	à détruire, c'est à dire normalement 0.
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

long	get_time(long t0)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000 - t0);
}

/*
	Met un thread en pause pendant un temps donné et en profite pour
	vérifier que le programme peut continuer.
*/
void	ft_usleep(t_data *data, long time_action)
{
	long	start_t;
	long	cur_t;

	start_t = get_time(0);
	cur_t = start_t;
	while (check_if_continue(data, &data->philo[0]) != -1
		&& (cur_t - start_t) < time_action)
	{
		usleep(100);
		cur_t = get_time(0);
	}
}
