/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:20:50 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/21 15:30:08 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
function that fills my args sturct after checking
that all the args are valide and safe to use
by the arg checker
*/
static int	parse_args(int argc, char **argv, t_args *args)
{
	if (argc != 9)
	{
		printf("ERROR: Expected 9 arguments, got %d\n", argc);
		return (FAILED);
	}
	args->number_of_coders = ft_atol(argv[1]);
	args->time_to_burnout = ft_atol(argv[2]);
	args->time_to_compile = ft_atol(argv[3]);
	args->time_to_debug = ft_atol(argv[4]);
	args->time_to_refactor = ft_atol(argv[5]);
	args->number_of_compiles_required = ft_atol(argv[6]);
	args->dongle_cooldown = ft_atol(argv[7]);
	if (strcmp(argv[8], "fifo") == 0)
		args->scheduler = FIFO;
	else
		args->scheduler = EDF;
	return (SUCCESS);
}

// the scheduler checker
static int	check_scheduler(char *arg)
{
	if (strcmp(arg, "fifo") != 0 && strcmp(arg, "edf") != 0)
	{
		printf("ERROR: scheduler must be 'fifo' or 'edf'\n");
		return (FAILED);
	}
	return (SUCCESS);
}

/*
helper for the check_args function that helps with sanitaizing
the giving args to only take the valide ones
*/
static int	check_args_help(t_ull num, int i)
{
	if (num > INT_MAX)
	{
		printf("ERROR: only integers are allowed\n");
		return (FAILED);
	}
	if (i == 1 && num < 1)
	{
		printf("ERROR: number_of_coders must be >= 1\n");
		return (FAILED);
	}
	if (i >= 2 && i <= 5 && num == 0)
	{
		printf("ERROR: time values must be > 0\n");
		return (FAILED);
	}
	if (i == 6 && num < 1)
	{
		printf("ERROR: number_of_compiles_required must be >= 1\n");
		return (FAILED);
	}
	return (SUCCESS);
}

/*
function to check if the args is is valid
before working with them
*/
static int	check_args(char **argv)
{
	int		i;
	t_ull	num;

	i = 1;
	while (i < 8)
	{
		if (!is_number(argv[i]))
		{
			printf("ERROR: invalid number\n");
			return (FAILED);
		}
		if (argv[i][0] == '-')
		{
			printf("ERROR: negative numbers are not allowed\n");
			return (FAILED);
		}
		num = ft_atol(argv[i]);
		if (check_args_help(num, i) == FAILED)
			return (FAILED);
		i++;
	}
	if (check_scheduler(argv[8]) == FAILED)
		return (FAILED);
	return (SUCCESS);
}

// the main parsing wrapper
/*
validate the argument passed before
starting to parse them
*/

t_args	*parser(int argc, char **argv)
{
	t_args	*args;

	if (check_args(argv) == FAILED)
		return (NULL);
	args = safe_malloc(sizeof(t_args));
	if (args == NULL)
		return (NULL);
	if (parse_args(argc, argv, args) == FAILED)
	{
		free(args);
		return (NULL);
	}
	return (args);
}
