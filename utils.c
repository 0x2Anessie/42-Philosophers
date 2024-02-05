/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acatusse <acatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:07:02 by acatusse          #+#    #+#             */
/*   Updated: 2024/02/02 17:15:20 by acatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r')
		|| nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	if ((sign * nb) < INT_MIN || (sign * nb) > INT_MAX)
		return (-1);
	return ((int)sign * nb);
}

long	get_time(long t0)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000 - t0);
}

int	check_philo_continue(t_data *data, t_philo *philo)
{
	(void)philo;
	pthread_mutex_lock(&data->mutex_check);
	if (data->someone_died || data->fini == 0)
	{
		pthread_mutex_unlock(&data->mutex_check);
		return (-1);
	}
	pthread_mutex_unlock(&data->mutex_check);
	return (1);
}

void	print_meal(t_philo *philo)
{
	if (check_philo_continue(philo->data, philo) != -1)
	{
		printf("%ld: 	\033[35mʚ\033[0mphilo %d\033[35mɞ\033[0m has taken a" \
			" fork\n", philo->time, philo->id);
		printf("%ld: 	\033[35mʚ\033[0mphilo %d\033[35mɞ\033[0m has taken a" \
			" fork\n", philo->time, philo->id);
		printf("%ld: 	\033[35mʚ\033[0mphilo %d\033[35mɞ" \
			"\033[0m \033[32mis eating\n\033[0m", philo->time, philo->id);
	}
}

void	ft_usleep(t_data *data, long time_action)
{
	long	start_t;
	long	cur_t;

	start_t = get_time(0);
	cur_t = start_t;
	while (check_philo_continue(data, &data->philo[0]) != -1
		&& (cur_t - start_t) < time_action)
	{
		usleep(100);
		cur_t = get_time(0);
	}
}
