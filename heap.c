/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 15:47:21 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/11 17:33:22 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	heap_remove_at(t_heap *heap, int index, char *scheduler)
{
	int	parent;

	heap->size--;
	if (index == heap->size)
		return ;
	heap->items[index] = heap->items[heap->size];
	parent = (index - 1) / 2;
	if (index > 0 && request_before(&heap->items[index],
			&heap->items[parent], scheduler))
		heap_sift_up(heap, index, scheduler);
	else
		heap_sift_down(heap, index, scheduler);
}

int	init_heap(t_heap *heap, int capacity)
{
	if (capacity <= 0)
		return (1);
	heap->items = malloc(sizeof(t_request) * capacity);
	if (heap->items == NULL)
		return (1);
	heap->size = 0;
	heap->capacity = capacity;
	return (0);
}
