/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_coder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 14:03:44 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/12 16:49:16 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	single_coder(t_coder *coder)
{
	print_status(coder, "has taken a dongle");
	while (!get_stop(coder->sim))
	{
		usleep(1000);
	}
}
