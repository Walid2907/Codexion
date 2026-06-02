/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 00:30:31 by wkerdad           #+#    #+#             */
/*   Updated: 2026/05/26 00:54:39 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
    int scheduler;
}			t_args;


t_args *parser(char **args);

# endif