/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 15:55:42 by lalexk-ku         #+#    #+#             */
/*   Updated: 2023/01/20 15:10:23 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (!n || !s1 || !s2)
	{
		return (0);
	}
	i = 0;
	while (*s1 && *s2 && (*s1 == *s2) && (i + 1 < n))
	{
		++s1;
		++s2;
		++i;
	}
	return (((unsigned char)*s1) - ((unsigned char)*s2));
}
