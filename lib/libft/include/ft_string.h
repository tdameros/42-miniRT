/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:08:57 by vfries            #+#    #+#             */
/*   Updated: 2023/03/05 19:28:10 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stddef.h>
# include <stdbool.h>

char	**ft_split_set(char const *s, char *set);
char	**ft_split(char const *s, char c);
size_t	ft_split_size(char **strs);
void	ft_free_split(void *strs);
char	**ft_split_unless_in_quotes(char *arg);
size_t	ft_count_args_after_split_unless_quotes(char *arg);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_join_strs(char **strs, char const *sep);
char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3);

bool	ft_is_number(char *s);
char	*ft_skip_char(const char *str, char c);
char	*ft_skip_set(const char *str, const char *set);
bool	ft_str_is_in_strs(char *str, char **strs);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strcmp_ignore_case(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrstr(const char *haystack, const char *needle);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
