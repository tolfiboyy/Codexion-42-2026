/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:35:35 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/12 17:09:56 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	set_finished(t_coder *coder, int value)
{
	pthread_mutex_lock(&coder->time_mutex);
	if (value != 0)
		coder->finished = 1;
	else
		coder->finished = 0;
	pthread_mutex_unlock(&coder->time_mutex);
}

int	init_stop(t_simulation *sim)
{
	sim->stop = 0;
	if (pthread_mutex_init(&sim->stop_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	get_stop(t_simulation *sim)
{
	int	stop;

	pthread_mutex_lock(&sim->stop_mutex);
	stop = sim->stop;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (stop);
}

void	set_stop(t_simulation *sim, int value)
{
	pthread_mutex_lock(&sim->stop_mutex);
	if (value != 0)
		sim->stop = 1;
	else
		sim->stop = 0;
	pthread_mutex_unlock(&sim->stop_mutex);
}
