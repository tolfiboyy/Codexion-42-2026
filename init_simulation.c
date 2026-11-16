/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:59:56 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/12 16:48:12 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_dongles(t_simulation *sim)
{
	int	i;

	sim->dongle = malloc(sizeof(t_dongle) * sim->config.number_of_coders);
	if (sim->dongle == NULL)
		return (1);
	i = 0;
	while (i < sim->config.number_of_coders)
	{
		sim->dongle[i].id = i + 1;
		sim->dongle[i].available = 1;
		sim->dongle[i].ready_at_ms = 0;
		i++;
	}
	return (0);
}

int	init_coders(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->coder = malloc(sizeof(t_coder) * sim->config.number_of_coders);
	if (sim->coder == NULL)
		return (1);
	while (i < sim->config.number_of_coders)
	{
		sim->coder[i].id = i + 1;
		sim->coder[i].finished = 0;
		sim->coder[i].left = &sim->dongle[i];
		sim->coder[i].right = &sim->dongle[
			(i + sim->config.number_of_coders - 1)
			% sim->config.number_of_coders];
		sim->coder[i].sim = sim;
		if (pthread_mutex_init(&sim->coder[i].time_mutex, NULL) != 0)
		{
			cleanup_coders(sim->coder, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_manager(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->gestion_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->gestion_mutex);
		return (1);
	}
	sim->next_sequence = 0;
	return (0);
}

int	init_base(t_simulation *sim)
{
	if (init_dongles(sim))
		return (1);
	if (init_coders(sim))
	{
		free(sim->dongle);
		return (1);
	}
	if (init_stop(sim))
	{
		cleanup_coders(sim->coder, sim->config.number_of_coders);
		free(sim->dongle);
		return (1);
	}
	return (0);
}

int	init_simulation(t_simulation *sim)
{
	sim->threads = NULL;
	sim->heap.items = NULL;
	if (init_base(sim))
		return (1);
	if (init_manager(sim))
	{
		pthread_mutex_destroy(&sim->stop_mutex);
		cleanup_coders(sim->coder, sim->config.number_of_coders);
		free(sim->dongle);
		return (1);
	}
	if (init_heap(&sim->heap, sim->config.number_of_coders))
	{
		cleanup_simulation(sim);
		return (1);
	}
	return (0);
}
