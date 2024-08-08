/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:10:57 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/05 07:08:37 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_tabsize(const char *str, char c)
{
	int	size;

	size = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
			size++;
		while (*str && *str != c)
			str++;
	}
	return (size);
}

static int	ft_wordlen(const char *str, char c)
{
	int	len;

	len = 0;
	while (*str && *str == c)
		str++;
	while (*str && *str != c)
	{
		str++;
		len++;
	}
	return (len);
}

static char	*ft_cpyword(const char *str, char c)
{
	char	*word;
	int		i;
	int		len;

	len = ft_wordlen(str, c);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	*ft_free_tab(char **tab, int size)
{
	while (size >= 0)
	{
		free(tab[size]);
		size--;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (0);
	tab = (char **)malloc(sizeof(char *) * (ft_tabsize(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			tab[i] = ft_cpyword(s, c);
			if (!tab[i])
				return (ft_free_tab(tab, i));
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	tab[i] = NULL;
	return (tab);
}
