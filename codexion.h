/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 00:30:31 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/10 18:55:11 by wkerdad          ###   ########.fr       */
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

# define loong_t unsigned long long

typedef struct s_args
{
    loong_t number_of_coders;
    loong_t time_to_burnout;
    loong_t time_to_compile;
    loong_t time_to_debug;
    loong_t time_to_refactor;
    loong_t number_of_compiles_required;
    loong_t dongle_cooldown;
    char *scheduler;

}			t_args;

typedef struct s_dongle
{
    pthread_mutex_t dongle;
    int dongle_id;
    loong_t status;
    pthread_cond_t cond;
}           t_dongle;

typedef struct s_coder
{
    int coder_id;
    loong_t compile_counter;
    // B.S
    loong_t last_compile;
    int status;
    t_dongle *left_hand;
    t_dongle *right_hand;
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
void *safe_malloc(size_t size);

# endif