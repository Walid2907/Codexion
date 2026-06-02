/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 23:58:02 by wkerdad           #+#    #+#             */
/*   Updated: 2026/05/26 00:57:04 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int main(int argc, char **argv)
{
    if (argc != 9)
    {
        printf(
            "usage:<./codexion number_of_coders time_to_burnout time_to_compile"
            "time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler>"
        );
        return 0;
    }
    t_args *data = parser(argv);
    printf("%llu", data->number_of_coders);
}