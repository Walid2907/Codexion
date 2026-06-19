/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 00:16:53 by wkerdad           #+#    #+#             */
/*   Updated: 2026/06/19 18:57:19 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void parse_args(char **argv, t_args *data)
{
    data->number_of_coders = ft_atol(argv[1]);
    data->time_to_burnout = ft_atol(argv[2]);
    data->time_to_compile = ft_atol(argv[3]);
    data->time_to_debug = ft_atol(argv[4]);
    data->time_to_refactor = ft_atol(argv[5]);
    data->number_of_compiles_required = ft_atol(argv[6]);
    data->dongle_cooldown = ft_atol(argv[7]);
    data->scheduler = argv[8];
}

t_args *parser(char **args)
{
    t_args *data;

    data = malloc(sizeof(t_args));
    if (!data)
        return (NULL);
    parse_args(args, data);
    return (data);
}