#include "philosophers.h"

/*
	Vérifie que les arguments passés au programme soient des nombres.
	Compte le nombre de digit qui compose chaque argument et renvoie
	une erreur si un argument comporte plus de 10 digits.
*/
int	check_arg(int argc, char **argv)
{
	int	i;
	int	arg;
	int	significant_digits;

	arg = 1;
	while (arg <= (argc - 1))
	{
		i = 0;
		significant_digits = 0;
		if (argv[arg][i] == '-' || argv[arg][i] == '+')
			i++;
		while (argv[arg][i])
		{
			if (!(argv[arg][i] >= '0' && argv[arg][i] <= '9'))
				return (printf("\033[31mArguments must be numbers! \
						\n\033["), 1);
			significant_digits += argv[arg][i] != 0;
			i++;
		}
		if (significant_digits > 10)
			return (printf("\033[31mOne of your args is too long, they" \
					" each arg should be shorter than 10 digits!\n\033["), 1);
		arg++;
	}
	return (0);
}

int	rules_parsing(t_rules *rules)
{
	if (rules->nbr_philo <= 0 || rules->time_to_die <= 0 || \
		rules->time_to_eat <= 0 || rules->time_to_sleep <= 0)
	{
		printf("\033[31mWrong arguments !\n\033[");
		return (1);
	}
	return (0);
}
