/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 13:40:05 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/12 17:09:00 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;
	int				i;

	sim = (t_simulation *)arg;
	while (!get_stop(sim))
	{
		i = 0;
		while (i < sim->config.number_of_coders)
		{
			if (check_for_burnout(&sim->coder[i]))
			{
				print_status(&sim->coder[i], "burned out");
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
