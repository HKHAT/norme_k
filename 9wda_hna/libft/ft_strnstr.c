/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:27:21 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/05 07:08:32 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i] && little[j])
	{
		if (big[i] == little[j])
		{
			i++;
			j++;
			if (j == ft_strlen(little))
				return ((char *)big + i - j);
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	l;
	size_t	i;
	char	*p;

	i = 0;
	if (s == NULL)
		return (0);
	l = ft_strlen(s);
	while (i + start < l && i < len)
		i++;
	p = malloc(i + 1);
	if (!p)
		return (0);
	l = 0;
	while (i > 0)
	{
		p[l++] = s[start++];
		i--;
	}
	p[l] = '\0';
	return (p);
}
