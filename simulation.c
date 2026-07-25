/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:01:13 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/21 15:29:26 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
the codes routine
start by waiting for all the thread (brothers)
and then start it's cycle of compiling debugging
and refactoring while he's not done
and the simulation is not done
*/
static void	*routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	wait_all_thread(coder->data);
	while (get_bool(&coder->data->simulation_done_mutex,
			&coder->data->simulation_done) == false)
	{
		if (get_bool(&coder->is_done_mutex, &coder->is_done) == true)
			break ;
		if (compile(coder) == FAILED)
			break ;
		print_msg(coder, DEBUGE);
		ft_usleep(coder->data->args->time_to_debug, coder->data);
		print_msg(coder, REFACTOR);
		ft_usleep(coder->data->args->time_to_refactor, coder->data);
	}
	return (NULL);
}

static void	*burnout_helper(t_data *data, int *all_done)
{
	int		i;
	t_ull	time_to_compile;

	i = -1;
	while (++i < data->args->number_of_coders)
	{
		if (get_bool(&data->coders_arr[i].is_done_mutex,
				&data->coders_arr[i].is_done) == false)
		{
			*all_done = 0;
			time_to_compile = data->args->time_to_burnout;
			if (get_time() - get_long(&data->coders_arr[i].last_compile_mutex,
					&data->coders_arr[i].last_compile) > (t_ull)time_to_compile)
			{
				safe_mutex(LOCK, &data->print_msg_mutex);
				set_bool(&data->simulation_done_mutex, &data->simulation_done,
					true);
				printf("%llu %d burned out\n", get_time()
					- data->simulation_start, data->coders_arr[i].coder_id);
				safe_mutex(UNLOCK, &data->print_msg_mutex);
				return (NULL);
			}
		}
	}
	return ((void *)1);
}

/*
burnout monitore
the guardian of all the coders
it check if any of the coders had burned out
or all of them had finished
and then change the simulation status to done
*/
static void	*burnout_monitor(void *arg)
{
	t_data	*data;
	int		all_done;

	data = (t_data *)arg;
	wait_all_thread(data);
	while (1)
	{
		all_done = 1;
		if (burnout_helper(data, &all_done) == NULL)
			return (NULL);
		if (all_done)
		{
			set_bool(&data->simulation_done_mutex, &data->simulation_done,
				true);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}

int	sim_start_helper(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args->number_of_coders)
	{
		if (safe_thread(CREATE, &data->coders_arr[i].th, routine,
				&data->coders_arr[i]) == FAILED)
		{
			data->simulation_done = true;
			while (--i >= 0)
				safe_thread(JOIN, &data->coders_arr[i].th, NULL, NULL);
			return (FAILED);
		}
		i++;
	}
	return (SUCCESS);
}

/*
the start of the simaulation
we create all the threads (coders)
so they can start there routines
and starting the sim timer when all the coders are ready
and then joinig them with the main thread so it can wait for them
all safe
*/
int	sim_start(t_data *data)
{
	int			i;
	pthread_t	monitor;

	if (sim_start_helper(data) == FAILED)
		return (FAILED);
	safe_thread(CREATE, &monitor, burnout_monitor, data);
	safe_mutex(LOCK, &data->data_mutex);
	data->simulation_start = get_time();
	safe_mutex(UNLOCK, &data->data_mutex);
	i = 0;
	while (i < data->args->number_of_coders)
	{
		set_long(&data->coders_arr[i].last_compile_mutex,
			&data->coders_arr[i].last_compile, data->simulation_start);
		i++;
	}
	set_bool(&data->all_th_rd_mutex, &data->all_th_rd, true);
	i = 0;
	while (i < data->args->number_of_coders)
	{
		safe_thread(JOIN, &data->coders_arr[i].th, NULL, NULL);
		i++;
	}
	safe_thread(JOIN, &monitor, NULL, NULL);
	return (SUCCESS);
}
