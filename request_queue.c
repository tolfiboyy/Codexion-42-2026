/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_queue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 16:59:03 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/12 15:44:40 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	share_dongles(t_coder *a, t_coder *b)
{
	if (a->right == b->left || a->left == b->right)
		return (1);
	return (0);
}

int	try_grant_request(t_coder *coder)
{
	t_simulation	*sim;
	int				i;
	int				j;

	i = 0;
	sim = coder->sim;
	while (i < sim->heap.size && sim->heap.items[i].coder != coder)
		i++;
	if (i == sim->heap.size || !can_take_dongles(coder, get_time_ms()))
		return (0);
	j = 0;
	while (j < sim->heap.size)
	{
		if (request_before(&sim->heap.items[j], &sim->heap.items[i],
				sim->config.scheduler)
			&& share_dongles(sim->heap.items[j].coder,
				sim->heap.items[i].coder)
			&& can_take_dongles(sim->heap.items[j].coder, get_time_ms()))
			return (0);
		j++;
	}
	reserve_dongles(coder);
	heap_remove_at(&sim->heap, i, sim->config.scheduler);
	return (1);
}

int	can_take_dongles(t_coder *coder, long long now)
{
	if (coder->left == coder->right)
		return (0);
	if (now >= coder->left->ready_at_ms
		&& now >= coder->right->ready_at_ms
		&& coder->left->available
		&& coder->right->available)
		return (1);
	return (0);
}

void	reserve_dongles(t_coder *coder)
{
	coder->left->available = 0;
	coder->right->available = 0;
}

void	release_dongles(t_coder *coder)
{
	t_simulation	*sim;
	long long		ready_at;

	sim = coder->sim;
	pthread_mutex_lock(&sim->gestion_mutex);
	ready_at = get_time_ms() + sim->config.dongle_cooldown;
	coder->left->available = 1;
	coder->right->available = 1;
	coder->left->ready_at_ms = ready_at;
	coder->right->ready_at_ms = ready_at;
	pthread_mutex_unlock(&sim->gestion_mutex);
}
