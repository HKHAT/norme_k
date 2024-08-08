/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:03:14 by yozainan          #+#    #+#             */
/*   Updated: 2024/05/28 20:44:32 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*result;
	size_t	i;

	i = 0;
	result = (char *)malloc(n + 1);
	if (!result)
		return (NULL);
	while (i < n && s[i] != '\0')
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup;

	if (!s)
		return (NULL);
	dup = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
