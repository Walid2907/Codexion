/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 02:35:50 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/21 15:29:55 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// timestamp_in_ms X (event)

static void	print_helper(t_coder *coder, t_time_op status, t_ull *time_stamp)
{
	if (status == DEBUGE)
		printf("%llu %d is debugging\n", *time_stamp, coder->coder_id);
	else if (status == REFACTOR)
		printf("%llu %d is refactoring\n", *time_stamp, coder->coder_id);
	else if (status == BURNED_OUT)
		printf("%llu %d burned out\n", *time_stamp, coder->coder_id);
	else
		printf("wrong opcode\n");
}

// debug function
static void	print_msg_debug(t_coder *coder, t_time_op status)
{
	t_ull	time_stamp;

	time_stamp = get_time() - coder->data->simulation_start;
	if (!get_bool(&coder->data->simulation_done_mutex,
			&coder->data->simulation_done))
	{
		if (status == TAKE_FIRST_DG)
			printf("%llu %d has taken a RIGHT dongle: %d\n", time_stamp,
				coder->coder_id, coder->right_hand->dongle_id);
		else if (status == TAKE_SECOND_DG)
			printf("%llu %d has taken a LEFT dongle: %d\n", time_stamp,
				coder->coder_id, coder->left_hand->dongle_id);
		else if (status == COMPILE)
		{
			printf("%llu %d is compiling: NUMBER of compiles: %d\n", time_stamp,
				coder->coder_id, get_int(&coder->compile_counter_mutex,
					&coder->compile_counter));
			printf("%d\n", get_bool(&coder->is_done_mutex, &coder->is_done));
		}
		else
			print_helper(coder, status, &time_stamp);
	}
}

/*
function to print the appearing meassage on the terminal
in a safe way using mutexes
!!!! change the DEBUG_MODE value to 1
in the header file if needed
*/
void	print_msg(t_coder *coder, t_time_op status)
{
	t_ull	time_stamp;

	if (get_bool(&coder->is_done_mutex, &coder->is_done))
		return ;
	if (DEBUG_MODE)
		print_msg_debug(coder, status);
	else
	{
		safe_mutex(LOCK, &coder->data->print_msg_mutex);
		time_stamp = get_time() - coder->data->simulation_start;
		if (!get_bool(&coder->data->simulation_done_mutex,
				&coder->data->simulation_done))
		{
			if (status == TAKE_FIRST_DG || status == TAKE_SECOND_DG)
				printf("%llu %d has taken a dongle\n", time_stamp,
					coder->coder_id);
			else if (status == COMPILE)
				printf("%llu %d is compiling\n", time_stamp, coder->coder_id);
			else
				print_helper(coder, status, &time_stamp);
		}
		safe_mutex(UNLOCK, &coder->data->print_msg_mutex);
	}
}
