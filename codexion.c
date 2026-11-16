/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 10:44:31 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/10 14:47:38 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;
	int				status;

	if (argc != 9)
		return (1);
	if (validate_args(argv))
		return (1);
	initialize_config(&sim.config, argv);
	if (validate_config(&sim.config))
		return (1);
	if (init_simulation(&sim))
		return (1);
	status = run_simulation(&sim);
	cleanup_simulation(&sim);
	return (status);
}
