/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 00:30:31 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/12 18:51:52 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <errno.h>

#define SUCCESS 1
#define FAILED 0

typedef unsigned long long loong_t;
typedef struct s_data t_data;


typedef enum s_move
{
    CREATE,
    JOIN,
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    COMPILE,
    DEBUG,
    REFACTOR,
    WAITING,
    COOLDOWN,
    READY
}       t_move;

typedef struct s_args
{
    int number_of_coders;
    int time_to_burnout;
    int time_to_compile;
    int time_to_debug;
    int time_to_refactor;
    int number_of_compiles_required;
    int dongle_cooldown;
    char *scheduler;

}			t_args;

typedef struct s_dongle
{
    pthread_mutex_t dongle;
    int dongle_id;
    t_move status;
}           t_dongle;

typedef struct s_coder
{
    int coder_id; // coder id
    int compile_counter; // how many compiles is done
    bool is_done; // does the compiles needed is done
    t_dongle *left_hand;
    t_dongle *right_hand;
    pthread_t thread_id;
    t_move status;
    t_data *data;
    // B.S
    loong_t last_compile;
}           t_coder;

typedef struct s_data
{
    pthread_mutex_t data_mutex;
    t_args *args;
    t_dongle *dongles;
    t_coder *coders;
    loong_t timer;
    bool end_sum;
    bool all_thread_ready; // to sync coders
    // B.S
    pthread_t *threads;
    int simulation_running;
}           t_data;


// helper functions
loong_t	ft_atol(const char *nptr);
int is_number(const char *s);

// parsing
t_args *parser(int argc, char **args);

// initializer
int    init(t_data	*data);

// wrappers
void    *safe_malloc(size_t size);
int    safe_pthread(t_move move, pthread_t *th, void *(* holder)(void *), void *data);
int    safe_mutex(t_move move, pthread_mutex_t *mx);

// Setters and Getters
int    set_bool(pthread_mutex_t *mx, bool *to_set, bool value);
bool    get_bool(pthread_mutex_t *mx, bool *value);
int    set_int(pthread_mutex_t *mx, int *to_set, int value);
int    get_int(pthread_mutex_t *mx, int *value);
bool sim_finished(t_data *data);

//synchro function
void    wait_threads(t_data *data);

// simulation
int    simulation_start(t_data *data);

# endif