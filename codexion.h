/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 00:30:31 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/11 20:42:30 by wkerdad          ###   ########.fr       */
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

# define loong_t unsigned long long

typedef enum s_move
{
    CREATE,
    JOIN,
    LOCK,
    UNLOCK,
    INIT,
    DESTROY
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
    int status;
    pthread_cond_t cond;
}           t_dongle;

typedef struct s_coder
{
    int coder_id; // coder if
    int compile_counter; // how many compiles is done
    bool is_done; // does the compiles needed is done
    t_dongle *left_hand;
    t_dongle *right_hand;
    // B.S
    loong_t last_compile;
    int status;
}           t_coder;

typedef struct s_data
{
    t_args *args;
    t_dongle *dongles;
    t_coder *coders;
    loong_t timer;
    bool end_sum;
    // B.S
    pthread_t *threads;
    int simulation_running;
    pthread_mutex_t state_mutex;
}           t_data;


// helper functions
loong_t	ft_atol(const char *nptr);
int is_number(const char *s);

// parsing
t_args *parser(int argc, char **args);

// initializer
void    init(t_data	*data);

// wrappers
void    *safe_malloc(size_t size);
void    safe_pthread(t_move move, pthread_t *th, void *(* holder)(void *));
void    safe_mutex(t_move move, pthread_mutex_t *mx);

# endif