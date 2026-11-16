/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_queue2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 14:35:21 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/11 15:53:32 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	enqueue_request(t_coder *coder)
{
	t_simulation	*sim;
	t_request		request;
	int				status;

	sim = coder->sim;
	request.coder = coder;
	pthread_mutex_lock(&coder->time_mutex);
	request.deadline = coder->last_compile_time + sim->config.time_to_burnout;
	pthread_mutex_unlock(&coder->time_mutex);
	pthread_mutex_lock(&sim->gestion_mutex);
	request.sequence = sim->next_sequence++;
	status = heap_push(&sim->heap, request, sim->config.scheduler);
	pthread_mutex_unlock(&sim->gestion_mutex);
	return (status);
}

int	wait_for_dongles(t_coder *coder)
{
	t_simulation	*sim;

	sim = coder->sim;
	if (enqueue_request(coder))
		return (0);
	pthread_mutex_lock(&sim->gestion_mutex);
	while (!get_stop(sim))
	{
		if (try_grant_request(coder))
		{
			pthread_mutex_unlock(&sim->gestion_mutex);
			return (1);
		}
		pthread_mutex_unlock(&sim->gestion_mutex);
		usleep(1000);
		pthread_mutex_lock(&sim->gestion_mutex);
	}
	pthread_mutex_unlock(&sim->gestion_mutex);
	return (0);
}
