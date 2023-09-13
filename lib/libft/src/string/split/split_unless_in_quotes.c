/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 21:20:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/28 21:20:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_string.h"

static char	*add_word(char *arg, char **ret, int ret_index,
				const char *characters_to_split_on);
static int	get_word_size(char *arg, const char *characters_to_split_on);

char	**ft_split_unless_in_quotes(char *arg,
			const char *characters_to_split_on)
{
	char	**ret;
	size_t	arg_count;
	size_t	i;

	arg_count = ft_count_args_after_split_unless_quotes(arg,
			characters_to_split_on);
	ret = malloc(sizeof(char *) * (arg_count + 1));
	if (ret == NULL)
		return (NULL);
	i = -1;
	while (++i < arg_count)
	{
		arg = ft_skip_chars(arg, characters_to_split_on);
		arg = add_word(arg, ret, i, characters_to_split_on);
		if (ret[i] == NULL)
		{
			ft_free_split(ret);
			return (NULL);
		}
	}
	ret[arg_count] = NULL;
	return (ret);
}

size_t	ft_count_args_after_split_unless_quotes(char *arg,
			const char *characters_to_split_on)
{
	int	count;

	count = 0;
	while (*arg)
	{
		arg = ft_skip_chars(arg, characters_to_split_on);
		if (*arg)
			count++;
		arg += get_word_size(arg, characters_to_split_on);
	}
	return (count);
}

static char	*add_word(char *arg, char **ret, int ret_index,
				const char *characters_to_split_on)
{
	int		size;
	char	*new_word;

	size = get_word_size(arg, characters_to_split_on);
	new_word = malloc(sizeof(char) * ++size);
	if (new_word != NULL)
		ft_strlcpy(new_word, arg, size);
	ret[ret_index] = new_word;
	return (arg + size - 1);
}

static int	get_word_size(char *arg, const char *characters_to_split_on)
{
	int		size;
	bool	is_in_double_quote;
	bool	is_in_simple_quote;

	size = 0;
	is_in_double_quote = false;
	is_in_simple_quote = false;
	while (arg[size] != '\0')
	{
		if (arg[size] == '\"' && is_in_simple_quote == false)
			is_in_double_quote = !is_in_double_quote;
		else if (arg[size] == '\'' && is_in_double_quote == false)
			is_in_simple_quote = !is_in_simple_quote;
		else if (ft_strchr(characters_to_split_on, arg[size]) != NULL
			&& is_in_double_quote == false && is_in_simple_quote == false)
			break ;
		size++;
	}
	return (size);
}
