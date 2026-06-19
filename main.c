/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 23:58:02 by wkerdad           #+#    #+#             */
/*   Updated: 2026/06/19 19:03:14 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void	check_scheduler(char *arg)
{
	if (ft_strcmp(arg, "fifo") != 0 && ft_strcmp(arg, "edf") != 0)
	{
		printf("ERROR: scheduler must be 'fifo' or 'edf'\n");
		exit(1);
	}
}
void	check_args(int argc, char **argv)
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
		num = ft_atol(argv[i]);
		if ((i == 1 || i == 6) && (num < 1 || num > INT_MAX))
        {
			printf("ERROR: number_of_coders must be >= 1");
            exit(1);
        }
		else if (i == 6 && (num < 1 || num > INT_MAX))
        {
			printf("ERROR: number_of_compiles_required must be >= 1");
            exit(1);
        }
		else if (i == 2 && (num <= 0 || num > INT_MAX))
        {
			printf("ERROR: time_to_burnout must be > 0");
            exit(1);
        }
		else if (i == 3 && (num < 0 || num > INT_MAX))
        {
			printf("ERROR: time_to_compile must be >= 0");
            exit(1);
        }
		else if (i == 4 && (num < 0 || num > INT_MAX))
        {
			printf("ERROR: time_to_debug must be >= 0");
            exit(1);
        }
		else if (i == 5 && (num < 0 || num > INT_MAX))
        {
			printf("ERROR: time_to_refactor must be >= 0");
            exit(1);
        }
		else if (i == 7 && (num < 0 || num > INT_MAX))
        {
			printf("ERROR: dongle_cooldown must be >= 0");
            exit(1);
        }
		i++;
	}
    check_scheduler(argv[8]);
}

void args_init(char **argv)
{

}

int	main(int argc, char **argv)
{
	if (argc != 9)
	{
		printf("usage:<./codexion number_of_coders"
			"time_to_burnout time_to_compile"
			"time_to_debug time_to_refactor number_of_compiles_required"
			"dongle_cooldown scheduler>");
		return (0);
	}
	check_args(argc, argv);
    t_args *data = parser(argv);
    printf("%llu", data->number_of_coders);
	return (0);
}
