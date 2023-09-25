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

# define WHITE_SPACES "\t\n\v\f\r "

typedef struct s_string
{
	char	*data;
	size_t	len;
}	t_string;

//	join/join_strs.c
char	*ft_join_strs(char **strs, char const *sep);

//	join/strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);

//	join/strjoin_three.c
char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3);

//	split/free_split.c
void	ft_free_split(void *strs);

//	split/split.c
char	**ft_split(char const *s, char c);

//	split/split_len.c
size_t	ft_split_len(char **strs);

//	split/split_set.c
char	**ft_split_set(char const *s, char *set);

//	split/split_unless_in_quotes.c
char	**ft_split_unless_in_quotes(char *arg,
			const char *characters_to_split_on);
size_t	ft_count_args_after_split_unless_quotes(char *arg,
			const char *characters_to_split_on);

//	split/strs_are_equals.c
bool	ft_strs_are_equal(char **strs1, char **strs2);

//	is_number.c
bool	ft_is_number(char *s);

//	skip_char.c
char	*ft_skip_char(const char *str, char c);

//	skip_chars.c
char	*ft_skip_chars(const char *str, const char *chars_to_skip);

//	skip_set.c
char	*ft_skip_set(const char *str, const char *set);

//	str_ends_with.c
bool	ft_str_ends_with(const char *str, const char *end);

//	str_is_in_strs.c
bool	ft_str_is_in_strs(char *str, char **strs);

//	strchr.c
char	*ft_strchr(const char *s, int c);

//	strcmp.c
int		ft_strcmp(const char *s1, const char *s2);

//	strcmp_ignore_case.c
int		ft_strcmp_ignore_case(const char *s1, const char *s2);

//	strdup.c
char	*ft_strdup(const char *s1);

//	striteri.c
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

//	strlcat.c
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

//	strlcpy.c
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

//	strlen.c
size_t	ft_strlen(const char *str);

//	strmapi.c
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

//	strncmp.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//	strnstr.c
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

//	strrchr.c
char	*ft_strrchr(const char *s, int c);

//	strrstr.c
char	*ft_strrstr(const char *haystack, const char *needle);

//	strtrim.c
char	*ft_strtrim(char const *s1, char const *set);

//	substr.c
char	*ft_substr(char const *s, unsigned int start, size_t len);

//	t_string_free.c
void	t_string_free(void *string);

#endif
