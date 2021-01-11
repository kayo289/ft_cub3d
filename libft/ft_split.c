/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 13:02:08 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/11 22:53:54 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			**ft_clear(char ***ans)
{
	unsigned int	i;

	i = 0;
	while ((*ans)[i])
	{
		free((*ans)[i]);
		(*ans)[i++] = NULL;
	}
	free(*ans);
	*ans = NULL;
	return (NULL);
}

static size_t		calc_target_word(const char *s, char c)
{
	size_t			i;
	size_t			len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			while (s[i] == c && s[i])
				i++;
	}
	return (len);
}

static void			ft_scpy(char *str1, char *str2, char *until)
{
	while (str2 < until)
		*(str1++) = *(str2++);
	*str1 = 0;
}

#include<stdio.h>

char				**ft_split(const char *s, char c)
{
	char			**ans;
	int				i;
	char			*temp;

	i = 0;
	if (!s)
		return (NULL);
	if (!(ans = (char **)malloc((calc_target_word(s, c) + 1) * sizeof(char *))))
		return (NULL);
	while (*s)
	{
		if (!(c == *s))
		{
			temp = (char *)s;
			while (*s && !(c == *s))
				s++;
			if (!(ans[i] = ft_calloc(s - temp + 1, sizeof(char))))
				return (ft_clear(&ans));
			ft_scpy(ans[i++], temp, (char *)s--);
		}
		s++;
	}
	printf("i:%d\n",i);
	ans[i] = NULL;
	return (ans);
}
