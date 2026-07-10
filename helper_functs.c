/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 16:01:40 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/08 18:06:16 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int ft_strlen(const char *s)
{
    int	i;

    i = 0;
    while (s[i])
        ++i;
    return (i);
}

int is_number(const char *s)
{
    int i = 0;

    if (!s || !s[0])
        return 0;

    /* Only allow optional leading sign for compatibility, but numbers should be positive */
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
	int	sign;
	loong_t	numb;

	sign = 1;
	numb = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		numb = (numb * 10) + (*nptr - '0');
		nptr++;
	}
	return (numb * sign);
}
