/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:23:11 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:25:50 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
<<<<<<< HEAD
=======
#include <linux/limits.h>
>>>>>>> 6b16524cecc1780fb656448c617d26512105777e

char	*ft_strdup(const char *s)
{
	char	*d;

<<<<<<< HEAD
	d = malloc(ft_strlen(s) + 1);
=======
	d = malloc(PATH_MAX + 1);
>>>>>>> 6b16524cecc1780fb656448c617d26512105777e
	if (d)
		ft_strlcpy(d, s, ft_strlen(s) + 1);
	return (d);
}
