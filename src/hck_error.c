/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hck_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabarij <nrabarij@student.42antanana>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:38:04 by nrabarij          #+#    #+#             */
/*   Updated: 2024/06/24 09:51:09 by nrabarij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/hck.h"

void	hck_error(int code)
{
	if (code == 1)
		dprintf(2, "There is an error\n");
	exit(code);
}
