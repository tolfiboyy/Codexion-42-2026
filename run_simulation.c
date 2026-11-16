/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 16:15:37 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/06 17:36:18 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	run_simulation(t_simulation *sim)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	sim->start_time = get_time_ms();
	while (i < sim->config.number_of_coders)
		sim->coder[i++].last_compile_time = sim->start_time;
	if (pthread_create(&monitor, NULL, monitor_routine, sim) != 0)
		return (1);
	if (init_threads(sim))
	{
		set_stop(sim, 1);
		pthread_join(monitor, NULL);
		return (1);
	}
	if (join_threads(sim, sim->config.number_of_coders))
	{
		set_stop(sim, 1);
		pthread_join(monitor, NULL);
		return (1);
	}
	set_stop(sim, 1);
	pthread_join(monitor, NULL);
	return (0);
}
