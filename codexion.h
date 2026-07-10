/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 00:30:31 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/08 18:03:55 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CODEXION_H
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
    pthread_mutex_t print_mutex;
    t_dongle *dongles;
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
    long compile_counter;
    loong_t last_compile;
    int status;
    t_dongle *left_hand;
    t_dongle *right_hand;
}           t_coder;

typedef struct s_table
{
    t_args *args;
    t_dongle *dongles;
    t_coder *coders;
    pthread_t *threads;
    int simulation_running;
    pthread_mutex_t state_mutex;
}           t_table;



t_args *parser(int argc, char **args);
loong_t	ft_atol(const char *nptr);
int is_number(const char *s);
char	to_lowercase(char c);
int	ft_strcmp(const char *s1, const char *s2);
void	check_scheduler(char *arg);
void    check_args_help(int num, int i);
void	check_args(char **argv);
void    init(t_args	*data);

# endif