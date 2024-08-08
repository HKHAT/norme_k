/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:22:07 by yozainan          #+#    #+#             */
/*   Updated: 2024/07/11 16:24:42 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

//  - Libc functions

size_t		ft_strlen(const char *s);
char		*ft_itoa(int n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strndup(const char *s, size_t n);
char		*ft_strdup(const char *s);
char		**ft_split(char const *s, char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
long long	ft_atoll(char *s);
int			ft_isspace(int c);
int			ft_isdigit(int c);
int			ft_isalpha(char c);
int			ft_isalnum(int c);
void		ft_putendl_fd(char *s, int fd);
int			ft_strchr(char *s, char c);
char		*ft_strrch_finder(char *s, char c);
char		*ft_strjoinc(char *s, char c, char *path);
void		*ft_memset(void *str, int c, size_t len);

#endif
