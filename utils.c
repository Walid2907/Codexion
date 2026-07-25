/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:34:02 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/21 15:30:37 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// check for numbers
int	is_number(const char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

// the name is enough
t_ull	ft_atol(const char *nptr)
{
	t_ull	numb;

	numb = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		numb = (numb * 10) + (*nptr - '0');
		nptr++;
	}
	return (numb);
}

// helper function for the cleaner
// destroy mutexex
static void	cleanup_mutexes(t_data *data)
{
	int	i;

	i = data->args->number_of_coders - 1;
	while (i >= 0)
	{
		safe_mutex(DESTROY, &data->dongles_arr[i].dongle_mutex);
		safe_mutex(DESTROY, &data->dongles_arr[i].available_at_mutex);
		safe_mutex(DESTROY, &data->dongles_arr[i].queue_mutex);
		pthread_cond_destroy(&data->dongles_arr[i].queue_cond);
		safe_mutex(DESTROY, &data->coders_arr[i].coder_mutex);
		safe_mutex(DESTROY, &data->coders_arr[i].is_done_mutex);
		safe_mutex(DESTROY, &data->coders_arr[i].compile_counter_mutex);
		safe_mutex(DESTROY, &data->coders_arr[i].last_compile_mutex);
		i--;
	}
	safe_mutex(DESTROY, &data->data_mutex);
	safe_mutex(DESTROY, &data->print_msg_mutex);
	safe_mutex(DESTROY, &data->all_th_rd_mutex);
	safe_mutex(DESTROY, &data->simulation_done_mutex);
}

/*
the cleaner function that free the allocated memory
dependeing on the failing point
and also clean the mutexes if needed
*/
int	cleanup(t_data *data, int code)
{
	if (code == 1)
	{
		free(data->args);
		free(data);
		return (FAILED);
	}
	if (code == 2)
	{
		free(data->coders_arr);
		free(data->dongles_arr);
		return (FAILED);
	}
	if (code == 3)
	{
		cleanup_mutexes(data);
		cleanup(data, 2);
		cleanup(data, 1);
		return (FAILED);
	}
	return (SUCCESS);
}

// function to increment an integer
// by 1 :/
void	increment_int(pthread_mutex_t *mutex, int *var)
{
	safe_mutex(LOCK, mutex);
	(*var)++;
	safe_mutex(UNLOCK, mutex);
}
