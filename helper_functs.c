/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 16:01:40 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/10 18:09:06 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int is_number(const char *s)
{
    int i = 0;

    if (!s || !s[0])
        return 0;

    /* numbers should be only positive */
    if (s[i] == '+' || s[i] == '-')
        i++;

    if (!s[i])
        return 0;

    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

loong_t	ft_atol(const char *nptr)
{
	loong_t	numb;

	numb = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		numb = (numb * 10) + (*nptr - '0');
		nptr++;
	}
	return (numb);
}
