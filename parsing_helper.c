/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 00:16:53 by wkerdad           #+#    #+#             */
/*   Updated: 2026/05/26 00:53:39 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void parse_args(char **argv, t_args *data)
{
    data->number_of_coders = atoi(argv[1]);
    data->time_to_burnout = atoi(argv[2]);
    data->time_to_compile = atoi(argv[3]);
    data->time_to_debug = atoi(argv[4]);
    data->time_to_refactor = atoi(argv[5]);
    data->number_of_compiles_required = atoi(argv[6]);
    data->dongle_cooldown = atoi(argv[7]);
    data->scheduler = atoi(argv[8]);
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