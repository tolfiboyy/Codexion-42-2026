/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 10:47:13 by asavidan          #+#    #+#             */
/*   Updated: 2026/11/12 17:23:17 by asavidan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_simulation	t_simulation;
// permet d'eviter une dependance circulaire de declaration
// regarde ton s_coder. Ca t'avais pas manque hein ?

typedef struct s_config
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles;
	int		dongle_cooldown;
	char	*scheduler;
}	t_config;

typedef struct s_dongle
{
	int			id;
	int			available;
	long long	ready_at_ms;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	int				finished;
	long long		last_compile_time;
	pthread_mutex_t	time_mutex;
	t_dongle		*left;
	t_dongle		*right;
	t_simulation	*sim;
}	t_coder;

typedef struct s_request
{
	t_coder		*coder;
	long long	sequence;
	long long	deadline;
}	t_request;

typedef struct s_heap
{
	t_request	*items;
	int			size;
	int			capacity;
}	t_heap;

typedef struct s_simulation
{
	t_config		config;
	t_heap			heap;
	t_coder			*coder;
	t_dongle		*dongle;
	pthread_t		*threads;
	int				stop;
	long long		start_time;
	long long		next_sequence;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	gestion_mutex;
	pthread_mutex_t	print_mutex;
}	t_simulation;

void				*routine(void *arg);
// parsing.c
int					is_number(char *str);
void				initialize_config(t_config *config, char **argv);
int					validate_args(char **argv);
int					validate_config(t_config *config);
// simulation.c
int					init_simulation(t_simulation *sim);
int					init_coders(t_simulation *sim);
int					init_dongles(t_simulation *sim);
// cleanup.c
void				cleanup_simulation(t_simulation *sim);
void				cleanup_coders(t_coder *coders, int count);
// threads.c
int					init_threads(t_simulation *sim);
int					join_threads(t_simulation *sim, int count);
// simulation_state.c
void				set_finished(t_coder *coder, int value);
int					init_stop(t_simulation *sim);
int					get_stop(t_simulation *sim);
void				set_stop(t_simulation *sim, int value);
// run_simulation.c
int					run_simulation(t_simulation *sim);
// time.c
long long			get_time_ms(void);
void				update_last_compile_time(t_coder *coder);
int					check_for_burnout(t_coder *coder);
int					smart_sleep(t_simulation *sim, long long duration_ms);
// monitoring.c
void				*monitor_routine(void *arg);
// single_coder.c
void				single_coder(t_coder *coder);
// scheduler.c
int					request_before(t_request *a, t_request *b, char *scheduler);
// heap.c
int					init_heap(t_heap *heap, int capacity);
void				heap_remove_at(t_heap *heap, int index, char *scheduler);
// heap_logic.c
void				swap_requests(t_request *a, t_request *b);
void				heap_sift_up(t_heap *heap, int i, char *scheduler);
void				heap_sift_down(t_heap *heap, int i, char *scheduler);
int					heap_push(t_heap *heap, t_request request, char *scheduler);
// request_queue.c
int					try_grant_request(t_coder *coder);
int					can_take_dongles(t_coder *coder, long long now);
void				reserve_dongles(t_coder *coder);
void				release_dongles(t_coder *coder);
// request_queue2.c
int					wait_for_dongles(t_coder *coder);
int					enqueue_request(t_coder *coder);
// print_logs.c
void				print_status(t_coder *coder, char *message);
#endif
