/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 11:12:32 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/12 12:04:45 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_status(t_coder *coder, char *message)
{
	pthread_mutex_lock(&coder->sim->print_mutex);
	if (!get_stop(coder->sim) || strcmp("burned out", message) == 0)
		printf("%lld %d %s\n",
			get_time_ms() - coder->sim->start_time, coder->id, message);
	pthread_mutex_unlock(&coder->sim->print_mutex);
}
