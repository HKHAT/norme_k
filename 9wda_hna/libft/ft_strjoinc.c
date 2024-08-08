/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:03:14 by yozainan          #+#    #+#             */
/*   Updated: 2024/07/28 23:29:58 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinc(char *s, char c, char *path)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (ft_strlen(s) + ft_strlen(path)) + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (*s)
		str[i++] = *s++;
	str[i++] = c;
	while (*path)
		str[i++] = *path++;
	str[i] = '\0';
	return (str);
}
