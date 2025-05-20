/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:29:38 by kdrazek           #+#    #+#             */
/*   Updated: 2025/05/19 14:36:19 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "so_long.h"

void	*ft_calloc(size_t n, size_t size)
{
	size_t			t;
	void			*ptr;
	unsigned char	*b;
	size_t			i;

	i = 0;
	if (n == 0 || size == 0)
		return (malloc(0));
	t = n * size;
	if (t / n != size)
		return (NULL);
	ptr = malloc(t);
	if (ptr == NULL)
		return (NULL);
	b = (unsigned char *)ptr;
	while (i < t)
	{
		b[i] = 0;
		i++;
	}
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}
