/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 00:16:53 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/12 15:17:11 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void parse_args(int argc, char **argv, t_args *args)
{
    if (argc != 9)
    {
        printf("ERROR: Expected 9 arguments, got %d\n", argc);
        exit(1);
    }
    // !! usleep work with microsecond (x * 1000)
    args->number_of_coders = ft_atol(argv[1]);
    args->time_to_burnout = ft_atol(argv[2]);
    args->time_to_compile = ft_atol(argv[3]);
    args->time_to_debug = ft_atol(argv[4]);
    args->time_to_refactor = ft_atol(argv[5]);
    args->number_of_compiles_required = ft_atol(argv[6]);
    args->dongle_cooldown = ft_atol(argv[7]);
    args->scheduler = argv[8];
}

// the scheduler checker
static int	check_scheduler(char *arg)
{
    if (strcmp(arg, "fifo") != 0 && strcmp(arg, "edf") != 0)
	{
        printf("ERROR: scheduler must be 'fifo' or 'edf'\n");
		return(FAILED);
	}
    return(SUCCESS);
}
// helper for the check_args function just for norms
static int check_args_help(loong_t num, int i)
{
    if (num > INT_MAX)
    {
        printf("ERROR: only integers are allowed\n");
        return(FAILED);
    }
    if (i == 1 && num <= 1)
    {
        printf("ERROR: number_of_coders must be > 1\n");
        return(FAILED);
    }
    if (i >= 2 && i <= 5 && num == 0)
    {
        printf("ERROR: time values must be > 0\n");
        return(FAILED);
    }
    if (i == 6 && num < 1)
    {
        printf("ERROR: number_of_compiles_required must be >= 1\n");
        return(FAILED);
    }
    return(SUCCESS);
}
// function to check if the args is is valid 
// before working with them
static int	check_args(char **argv)
{
    int		i;
	loong_t	num;
    
	i = 1;
	while (i < 8)
	{
        if (!is_number(argv[i]))
		{
            printf("ERROR: invalid number\n");
			return(FAILED);
		}
		/* input starting with - is rejected */
		if (argv[i][0] == '-')
		{
            printf("ERROR: negative numbers are not allowed\n");
			return(FAILED);
		}
		num = ft_atol(argv[i]);
        if (check_args_help(num, i) == FAILED)
            return(FAILED);
		i++;
	}
	if (check_scheduler(argv[8]) == FAILED)
        return(FAILED);
    return(SUCCESS);
}

t_args *parser(int argc, char **argv)
{
    t_args *args;

    if (check_args(argv) == FAILED)
        return (NULL);
    args = safe_malloc(sizeof(t_args));
    parse_args(argc, argv, args);
    
    return (args);
}