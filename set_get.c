/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 01:13:33 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/21 15:30:18 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// safe setters and getters
// to prevent raceconditions
bool	get_bool(pthread_mutex_t *mutex, bool *var)
{
	bool	value;

	safe_mutex(LOCK, mutex);
	value = *var;
	safe_mutex(UNLOCK, mutex);
	return (value);
}

void	set_bool(pthread_mutex_t *mutex, bool *var, bool value)
{
	safe_mutex(LOCK, mutex);
	*var = value;
	safe_mutex(UNLOCK, mutex);
}

int	get_int(pthread_mutex_t *mutex, int *var)
{
	int	value;

	safe_mutex(LOCK, mutex);
	value = *var;
	safe_mutex(UNLOCK, mutex);
	return (value);
}

t_ull	get_long(pthread_mutex_t *mutex, t_ull *var)
{
	t_ull	value;

	safe_mutex(LOCK, mutex);
	value = *var;
	safe_mutex(UNLOCK, mutex);
	return (value);
}

void	set_long(pthread_mutex_t *mutex, t_ull *var, t_ull value)
{
	safe_mutex(LOCK, mutex);
	*var = value;
	safe_mutex(UNLOCK, mutex);
}
