/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acatusse <acatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:05:58 by acatusse          #+#    #+#             */
/*   Updated: 2024/02/05 15:10:11 by acatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Verifie la validitée des nombres passés au programme ./philo, c'est a dire
	que ce soit des chiffres et qu'il n'y en ait pas plus de 10 par argument.
*/
int	check_arg(int argc, char **argv)
{
	int	i;
	int	j;
	int	count_significant_digits;

	i = 1;
	while (i <= argc - 1)
	{
		j = 0;
		count_significant_digits = 0;
		if (argv[i][j] == '-' || argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (printf("\033[31mArguments must be numbers! \
						\n\033["), 1);
			count_significant_digits += argv[i][j] != '0';
			j++;
		}
		if (count_significant_digits > 10)
			return (printf("\033[31mOne of your args is too long, they" \
					" each arg should be shorter than 10 digits!\n\033["), 1);
		i++;
	}
	return (0);
}

void	signal_print_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->mutex_check);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->mutex_check);
	pthread_mutex_lock(&data->write);
	printf("%ld %d died\n", get_time(data->t0), i);
	pthread_mutex_unlock(&data->write);
}

void	check_philo_life(t_data *data)
{
	int	i;
	int	time_last_meal;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex_check);
		time_last_meal = get_time(data->t0) - data->philo[i].time;
		pthread_mutex_unlock(&data->mutex_check);
		if (time_last_meal > data->global_rules.time_to_die)
			return (signal_print_death(data, i + 1));
		pthread_mutex_lock(&data->mutex_check);
		if (data->fini == 0)
		{
			pthread_mutex_unlock(&data->mutex_check);
			return ;
		}
		pthread_mutex_unlock(&data->mutex_check);
		i++;
		i = i % data->global_rules.nbr_philo;
	}
}
