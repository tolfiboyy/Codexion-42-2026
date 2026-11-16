/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 16:54:54 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/09 11:52:03 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_for_burnout(t_coder *coder)
{
	long long	elapsed;
	int			burned_out;

	burned_out = 0;
	elapsed = 0;
	pthread_mutex_lock(&coder->time_mutex);
	if (!coder->finished)
		elapsed = get_time_ms() - coder->last_compile_time;
	if (elapsed >= coder->sim->config.time_to_burnout)
	{
		set_stop(coder->sim, 1);
		burned_out = 1;
	}
	pthread_mutex_unlock(&coder->time_mutex);
	return (burned_out);
}

void	update_last_compile_time(t_coder *coder)
{
	pthread_mutex_lock(&coder->time_mutex);
	coder->last_compile_time = get_time_ms();
	pthread_mutex_unlock(&coder->time_mutex);
}

long long	get_time_ms(void)
{
	struct timeval	time_value;

	gettimeofday(&time_value, NULL);
	return (time_value.tv_sec * (long long)1000 + time_value.tv_usec / 1000);
}

int	smart_sleep(t_simulation *sim, long long duration_ms)
{
	long long	start;

	start = get_time_ms();
	while (get_time_ms() - start < duration_ms && !get_stop(sim))
	{
		usleep(1000);
	}
	if (get_stop(sim))
		return (0);
	return (1);
}
