/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 15:55:19 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/12 16:49:00 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	cleanup_coders(t_coder *coders, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&coders[i].time_mutex);
		i++;
	}
	free(coders);
}

void	cleanup_simulation(t_simulation *sim)
{
	free(sim->threads);
	free(sim->heap.items);
	pthread_mutex_destroy(&sim->gestion_mutex);
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->stop_mutex);
	cleanup_coders(sim->coder, sim->config.number_of_coders);
	free(sim->dongle);
}
