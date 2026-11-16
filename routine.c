/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 17:19:51 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/12 17:54:30 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	compile_coder(t_coder *coder)
{
	int	completed;

	if (!wait_for_dongles(coder))
		return (0);
	if (get_stop(coder->sim))
	{
		release_dongles(coder);
		return (0);
	}
	print_status(coder, "has taken a dongle");
	print_status(coder, "has taken a dongle");
	update_last_compile_time(coder);
	print_status(coder, "is compiling");
	completed = smart_sleep(coder->sim, coder->sim->config.time_to_compile);
	release_dongles(coder);
	return (completed);
}

int	work_cycle(t_coder *coder, int is_last)
{
	if (!compile_coder(coder))
		return (0);
	if (is_last)
		set_finished(coder, 1);
	if (is_last || get_stop(coder->sim))
		return (1);
	print_status(coder, "is debugging");
	if (!smart_sleep(coder->sim, coder->sim->config.time_to_debug))
		return (1);
	if (get_stop(coder->sim))
		return (1);
	print_status(coder, "is refactoring");
	smart_sleep(coder->sim, coder->sim->config.time_to_refactor);
	return (1);
}

void	*routine(void *arg)
{
	t_coder	*coder;
	int		compiles_done;

	coder = (t_coder *)arg;
	if (coder->left == coder->right)
	{
		single_coder(coder);
		return (NULL);
	}
	compiles_done = 0;
	while (compiles_done < coder->sim->config.number_of_compiles
		&& !get_stop(coder->sim))
	{
		if (work_cycle(coder,
				compiles_done + 1 == coder->sim->config.number_of_compiles))
			compiles_done++;
	}
	return (NULL);
}
