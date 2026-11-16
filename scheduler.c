/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 16:57:04 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/12 17:55:25 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	request_before(t_request *a, t_request *b, char *scheduler)
{
	if (strcmp(scheduler, "fifo") == 0)
		return (a->sequence < b->sequence);
	if (strcmp(scheduler, "edf") == 0)
	{
		if (a->deadline == b->deadline)
			return (a->sequence < b->sequence);
		return (a->deadline < b->deadline);
	}
	return (0);
}
