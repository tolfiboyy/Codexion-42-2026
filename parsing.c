/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 10:44:40 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/12 15:58:53 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	validate_config(t_config *config)
{
	if (config->number_of_coders <= 0
		|| config->time_to_burnout <= 0
		|| config->time_to_compile <= 0
		|| config->time_to_debug < 0
		|| config->time_to_refactor < 0
		|| config->number_of_compiles <= 0)
		return (1);
	return (0);
}

int	validate_args(char **argv)
{
	int	i;

	i = 1;
	while (i < 8)
	{
		if (!is_number(argv[i]))
			return (1);
		i++;
	}
	if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
		return (1);
	return (0);
}

void	initialize_config(t_config *config, char **argv)
{
	config->number_of_coders = atoi(argv[1]);
	config->time_to_burnout = atoi(argv[2]);
	config->time_to_compile = atoi(argv[3]);
	config->time_to_debug = atoi(argv[4]);
	config->time_to_refactor = atoi(argv[5]);
	config->number_of_compiles = atoi(argv[6]);
	config->dongle_cooldown = atoi(argv[7]);
	config->scheduler = argv[8];
}

int	is_number(char *str)
{
	int	i;
	int	digit;
	int	number;

	i = 0;
	number = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		digit = str[i] - '0';
		if (number > (INT_MAX - digit) / 10)
		{
			printf("Value too big ! (INT MAX)");
			return (0);
		}
		number = number * 10 + digit;
		i++;
	}
	return (1);
}
