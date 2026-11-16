/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 15:51:22 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/10 18:28:52 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	join_threads(t_simulation *sim, int count)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < count)
	{
		if (pthread_join(sim->threads[i], NULL) != 0)
			status = 1;
		i++;
	}
	return (status);
}

int	init_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->threads = malloc(sizeof(pthread_t) * sim->config.number_of_coders);
	if (sim->threads == NULL)
		return (1);
	while (i < sim->config.number_of_coders)
	{
		if (pthread_create(&sim->threads[i],
				NULL, routine, &sim->coder[i]) != 0)
		{
			set_stop(sim, 1);
			if (join_threads(sim, i) != 0)
			{
				return (1);
			}
			free(sim->threads);
			sim->threads = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}
