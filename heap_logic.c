/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 17:40:18 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/12 15:57:31 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	swap_requests(t_request *a, t_request *b)
{
	t_request	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	heap_sift_up(t_heap *heap, int i, char *scheduler)
{
	int			parent;

	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (!request_before(&heap->items[i],
				&heap->items[parent], scheduler))
			break ;
		swap_requests(&heap->items[i], &heap->items[parent]);
		i = parent;
	}
}

void	heap_sift_down(t_heap *heap, int i, char *scheduler)
{
	int	left_child;
	int	right_child;
	int	best;

	while (1)
	{
		left_child = 2 * i + 1;
		right_child = 2 * i + 2;
		best = i;
		if (left_child < heap->size
			&& request_before(&heap->items[left_child]
				, &heap->items[best], scheduler))
			best = left_child;
		if (right_child < heap->size
			&& request_before(&heap->items[right_child]
				, &heap->items[best], scheduler))
			best = right_child;
		if (best == i)
			break ;
		swap_requests(&heap->items[i], &heap->items[best]);
		i = best;
	}
}

int	heap_push(t_heap *heap, t_request request, char *scheduler)
{
	int	i;

	if (heap->size >= heap->capacity)
		return (1);
	i = heap->size;
	heap->items[i] = request;
	heap->size++;
	heap_sift_up(heap, i, scheduler);
	return (0);
}
