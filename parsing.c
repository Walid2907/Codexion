/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 00:16:53 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/08 18:09:06 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void parse_args(int argc, char **argv, t_args *data)
{
    if (argc != 9)
    {
        printf("ERROR: Expected 9 arguments, got %d\n", argc);
        exit(1);
    }
    data->number_of_coders = ft_atol(argv[1]);
    data->time_to_burnout = ft_atol(argv[2]);
    data->time_to_compile = ft_atol(argv[3]);
    data->time_to_debug = ft_atol(argv[4]);
    data->time_to_refactor = ft_atol(argv[5]);
    data->number_of_compiles_required = ft_atol(argv[6]);
    data->dongle_cooldown = ft_atol(argv[7]);
    data->scheduler = argv[8];
}

t_args *parser(int argc, char **args)
{
    t_args *data;

    data = malloc(sizeof(t_args));
    if (!data)
        return (NULL);
    parse_args(argc, args, data);
    return (data);
}

// the scheduler checker
void	check_scheduler(char *arg)
{
	if (strcmp(arg, "fifo") != 0 && strcmp(arg, "edf") != 0)
	{
		printf("ERROR: scheduler must be 'fifo' or 'edf'\n");
		exit(1);
	}
}
// helper for the check_args function just for norms
void check_args_help(loong_t num, int i)
{
    if (i == 1 && num < 1)
    {
        printf("ERROR: number_of_coders must be >= 1\n");
        exit(1);
    }
    if (i >= 2 && i <= 5 && num == 0)
    {
        printf("ERROR: time values must be > 0\n");
        exit(1);
    }
    if (i == 6 && num < 1)
    {
        printf("ERROR: number_of_compiles_required must be >= 1\n");
        exit(1);
    }
}
// function to check if the args is is valid 
// before working with them
void	check_args(char **argv)
{
	int		i;
	loong_t	num;

	i = 1;
	while (i < 8)
	{
		if (!is_number(argv[i]))
		{
			printf("ERROR: invalid number\n");
			exit(1);
		}
		/* input starting with - is rejected */
		if (argv[i][0] == '-')
		{
			printf("ERROR: negative numbers are not allowed\n");
			exit(1);
		}
		num = ft_atol(argv[i]);
        check_args_help(num, i);
		i++;
	}
	check_scheduler(argv[8]);
}