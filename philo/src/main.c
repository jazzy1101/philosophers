/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:42:53 by dabae             #+#    #+#             */
/*   Updated: 2024/04/18 12:46:19 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	err_msg(char *msg)
{
	errno = 1;
	printf("%s\n", msg);
	exit(1);
}

int	main(int ac, char **av)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	if (!param)
		err_msg("failed to malloc.\n");
	if (ac == 5 || ac == 6)
	{
		init_param(param, av + 1);
		init_philo(param);
		life_cycle(param);
	}
	else
	{
		free(param);
		err_msg("Insufficient or too many arguments\n");
	}
}
