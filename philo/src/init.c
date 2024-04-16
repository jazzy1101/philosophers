/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:42:55 by dabae             #+#    #+#             */
/*   Updated: 2024/04/16 16:39:06 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*Checking the arguements are all digits including sign*/
static int	is_digit(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][0] == '-' || args[i][0] == '+')
				j++;
			else if (args[i][j] < '0' || args[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

/*Checking the arguements are all positive numbers*/
static int	is_positive(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_atoi(str[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

/*Initializing the parameters*/
static void	init_param(t_param *param, char **args)
{
	if (is_digit(args) && is_positive(args))
	{
		param->tids = malloc(sizeof(pthread_t) * param->num_philo);
		if (!param->tids)
			err_msg("failed to malloc.\n");
		param->forks = malloc(sizeof(pthread_mutex_t) * param->num_philo);
		if (!param->forks)
			err_msg("failed to malloc.\n");
		pthread_mutex_init(&param->print, NULL);
		pthread_mutex_init(&param->dead, NULL);
		param->num_philo = ft_atoi(args[0]);
		param->time_to_die = ft_atoi(args[1]);
		param->time_to_eat = ft_atoi(args[2]);
		param->time_to_sleep = ft_atoi(args[3]);
		if (args[4] && args[4] > 0)
			param->num_must_eat = ft_atoi(args[4]);
		else
			param->num_must_eat = -1;
	}
	else
		return (err_msg("Invalid arguments. Please double-check.\n"));
}

/*Initializing philosophers and starting the life cycle*/

static void	init_philo(t_philo **philo, t_param *param)
{
	int			i;

	i = -1;
	while (++i < param->num_philo)
	{
		philo[i]->id = i;
		philo[i]->param = param;
		philo[i]->left_fork = &philo[i]->param->forks[i];
		if (i != 0)
			philo[i]->right_fork = &philo[i]->param->forks[i - 1];
		else
			philo[0]->right_fork = &philo[param->num_philo \
				- 1]->param->forks[param->num_philo - i];
		philo[i]->state = -1;
		philo[i]->num_eat = 0;
		philo[i]->time_last_meal = 0;
		philo[i]->thread = param->tids[i];
		pthread_mutex_init(&(philo[i]->left_fork), NULL);
		pthread_create(&(philo[i]->thread), NULL, life_cycle, philo[i]);
	}
	i = -1;
    while (++i < param->num_philo)
        pthread_join(param->tids[i], NULL);
}
