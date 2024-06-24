/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hck_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:54:10 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/24 13:54:47 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_max(double n1, double n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}

double	ft_abs(double x1)
{
	if (x1 < 0)
		return (-x1);
	return (x1);
}
