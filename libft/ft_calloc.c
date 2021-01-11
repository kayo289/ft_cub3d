/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 23:16:05 by kkikuchi          #+#    #+#             */
/*   Updated: 2020/07/15 16:57:36 by kkikuchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ans;
	size_t	total;

	total = count * size;
	if (!(ans = malloc(total)))
		return (NULL);
	ft_memset(ans, 0, total);
	return (ans);
}
