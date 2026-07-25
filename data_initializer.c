/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_initializer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 22:00:49 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/21 03:04:12 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
init the coders hand by pointing
to the possible dongles to take
and handling the deadlock
*/
static void	coders_hand_init(t_data *data, int position)
{
	data->coders_arr[position].left_hand = &data->dongles_arr[position];
	data->coders_arr[position].right_hand = &data->dongles_arr[(position + 1)
		% data->args->number_of_coders];
	if (data->coders_arr[position].coder_id % 2 == 0)
	{
		data->coders_arr[position].right_hand = &data->dongles_arr[position];
		data->coders_arr[position].left_hand = &data->dongles_arr[(position + 1)
			% data->args->number_of_coders];
	}
}

/*
initialize coders and it mutexex and vars
*/
static int	coder_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args->number_of_coders)
	{
		data->coders_arr[i].coder_id = i + 1;
		data->coders_arr[i].compile_counter = 0;
		data->coders_arr[i].is_done = false;
		data->coders_arr[i].last_compile = 0;
		data->coders_arr[i].data = data;
		safe_mutex(INIT, &data->coders_arr[i].coder_mutex);
		safe_mutex(INIT, &data->coders_arr[i].is_done_mutex);
		safe_mutex(INIT, &data->coders_arr[i].compile_counter_mutex);
		safe_mutex(INIT, &data->coders_arr[i].last_compile_mutex);
		coders_hand_init(data, i);
		i++;
	}
	return (SUCCESS);
}

static int	dongle_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args->number_of_coders)
	{
		data->dongles_arr[i].dongle_id = i + 1;
		data->dongles_arr[i].available_at = 0;
		data->dongles_arr[i].queue = NULL;
		if (safe_mutex(INIT, &data->dongles_arr[i].dongle_mutex) == FAILED
			|| safe_mutex(INIT,
				&data->dongles_arr[i].available_at_mutex) == FAILED
			|| safe_mutex(INIT, &data->dongles_arr[i].queue_mutex) == FAILED
			|| pthread_cond_init(&data->dongles_arr[i].queue_cond, NULL) != 0)
		{
			dongle_init_helper(data, &i);
			return (FAILED);
		}
		i++;
	}
	return (SUCCESS);
}

/*
initialize the mutexes in a safe world !!
*/
static int	init_mutexes(t_data *data)
{
	if (safe_mutex(INIT, &data->data_mutex) == FAILED)
		return (FAILED);
	if (safe_mutex(INIT, &data->print_msg_mutex) == FAILED)
	{
		safe_mutex(DESTROY, &data->data_mutex);
		return (FAILED);
	}
	if (safe_mutex(INIT, &data->all_th_rd_mutex) == FAILED)
	{
		safe_mutex(DESTROY, &data->data_mutex);
		safe_mutex(DESTROY, &data->print_msg_mutex);
		return (FAILED);
	}
	if (safe_mutex(INIT, &data->simulation_done_mutex) == FAILED)
	{
		safe_mutex(DESTROY, &data->data_mutex);
		safe_mutex(DESTROY, &data->print_msg_mutex);
		safe_mutex(DESTROY, &data->all_th_rd_mutex);
		return (FAILED);
	}
	return (SUCCESS);
}

/*
main data initializer entry
start by allocating the needed
before calling the mutex, dongle
and coder initializer
*/
int	data_init(t_data *data)
{
	data->coders_arr = safe_malloc(sizeof(t_coder)
			* data->args->number_of_coders);
	if (data->coders_arr == NULL)
		return (FAILED);
	data->dongles_arr = safe_malloc(sizeof(t_dongle)
			* data->args->number_of_coders);
	if (data->dongles_arr == NULL)
	{
		free(data->coders_arr);
		return (FAILED);
	}
	data->simulation_done = false;
	data->all_th_rd = false;
	if (init_mutexes(data) == FAILED)
		return (cleanup(data, 2));
	if (dongle_init(data) == FAILED)
		return (cleanup(data, 2));
	coder_init(data);
	return (SUCCESS);
}
