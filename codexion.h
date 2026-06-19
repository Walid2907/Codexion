/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 00:30:31 by wkerdad           #+#    #+#             */
/*   Updated: 2026/06/19 18:59:30 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

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


t_args *parser(char **args);
loong_t	ft_atol(const char *nptr);
int is_number(const char *s);
char	to_lowercase(char c);
int	ft_strcmp(const char *s1, const char *s2);

# endif