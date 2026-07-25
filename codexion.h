/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:08:16 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/25 15:09:08 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// define some macros for simplicity
# define FAILED 0
# define SUCCESS 1
# define DEBUG_MODE 0

// a typdef to define the scheduler for easy compares
typedef enum s_scheduler
{
	FIFO,
	EDF
}								t_scheduler;

typedef enum s_mutex_op
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}								t_mutex_op;

typedef enum s_thread_op
{
	CREATE,
	JOIN,
	DETACH
}								t_thread_op;

typedef enum s_print_op
{
	BURNED_OUT,
	COMPILE,
	DEBUGE,
	REFACTOR,
	TAKE_FIRST_DG,
	TAKE_SECOND_DG
}								t_time_op;
/*************************************************************/

typedef unsigned long long		t_ull;
// defining an abrv for the type
typedef struct s_data			t_data;
// declaring the typdef of data to use it recursively
typedef struct s_coder			t_coder;
// declaring the typdef of coder to use it recursively
typedef struct s_dongle			t_dongle;
// declaring the typdef of dongle to use it recursively
typedef struct s_args			t_args;
// declaring the typdef of args to use it recursively
typedef struct s_dongle_wait	t_dongle_wait;

struct							s_dongle_wait
{
	int							coder_id;
	t_ull						deadline;
	t_dongle_wait				*next;
};

// main struct that well store all and have acces to all the elements
typedef struct s_data
{
	t_coder						*coders_arr;
	t_dongle					*dongles_arr;
	t_args						*args;
	bool						simulation_done;
	t_ull						simulation_start;
	bool						all_th_rd;
	pthread_mutex_t				data_mutex;
	pthread_mutex_t				simulation_done_mutex;
	pthread_mutex_t				all_th_rd_mutex;
	pthread_mutex_t				print_msg_mutex;

}								t_data;

// struct that will holde the coder data
typedef struct s_coder
{
	int							coder_id;
	pthread_mutex_t				coder_mutex;
	int							compile_counter;
	bool						is_done;
	pthread_mutex_t				is_done_mutex;
	pthread_mutex_t				compile_counter_mutex;
	t_ull						last_compile;
	pthread_mutex_t				last_compile_mutex;
	t_dongle					*right_hand;
	t_dongle					*left_hand;
	pthread_t					th;
	t_data						*data;
	t_dongle_wait				wait_node;

}								t_coder;

// struct to holde the dongle data
typedef struct s_dongle
{
	int							dongle_id;
	pthread_mutex_t				dongle_mutex;
	t_ull						available_at;
	pthread_mutex_t				available_at_mutex;
	t_dongle_wait				*queue;
	pthread_mutex_t				queue_mutex;
	pthread_cond_t				queue_cond;

}								t_dongle;

// the struct that will holde the user arguments
typedef struct s_args
{
	int							number_of_coders;
	int							time_to_burnout;
	int							time_to_compile;
	int							time_to_debug;
	int							time_to_refactor;
	int							number_of_compiles_required;
	int							dongle_cooldown;
	t_scheduler					scheduler;

}								t_args;

/************************************************/
// Functions Declaration

// parsing and utils
int								cleanup(t_data *data, int code);
int								is_number(const char *s);
t_ull							ft_atol(const char *nptr);
t_args							*parser(int argc, char **argv);
void							wait_all_thread(t_data *data);
void							dongle_init_helper(t_data *data, int *i);

// wrappers
void							*safe_malloc(size_t size);
int								safe_mutex(t_mutex_op op,
									pthread_mutex_t *mutex);
int								safe_thread(t_thread_op op, pthread_t *thread,
									void *(*routine)(void *), void *arg);

// data_initializer
int								data_init(t_data *data);

// simulation
int								sim_start(t_data *data);

// set_get
bool							get_bool(pthread_mutex_t *mutex, bool *var);
void							set_bool(pthread_mutex_t *mutex, bool *var,
									bool value);
int								get_int(pthread_mutex_t *mutex, int *var);
t_ull							get_long(pthread_mutex_t *mutex, t_ull *var);
void							set_long(pthread_mutex_t *mutex, t_ull *var,
									t_ull value);
void							increment_int(pthread_mutex_t *mutex, int *var);

// time
t_ull							get_time(void);
void							ft_usleep(t_ull sleep_time, t_data *data);

// logs
void							print_msg(t_coder *coder, t_time_op status);

// compile
int								compile(t_coder *coder);

// queue (FIFO/EDF scheduling)
void							request_dongle(t_coder *coder, t_dongle *dongle,
									bool *lk);
void							helper_helper_2(t_coder *coder,
									t_dongle *dongle, bool *lk);
#endif
