/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 03:18:18 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/09 18:27:41 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (1)
	{
		if (s[i] == (char)c)
			return ((char *)s);
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
}
