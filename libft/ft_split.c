/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 09:44:51 by damateos          #+#    #+#             */
/*   Updated: 2024/01/21 12:42:08 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (!in_word && *s != c)
		{
			in_word = 1;
			count++;
		}
		if (in_word && *s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*clean_arr(char **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
	return (NULL);
}

static char	*make_word(char **arr, const char *start, size_t len)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	arr[i] = ft_substr(start, 0, len);
	if (!arr[i])
		return (clean_arr(arr, i));
	return (arr[i]);
}

static size_t	get_word_len(const char *word_start, char c)
{
	size_t	len;

	len = 0;
	while (word_start[len] != c && word_start[len])
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	size_t		words;
	const char	*word_start;
	char		**arr;

	if (!s)
		return (NULL);
	word_start = NULL;
	arr = (char **)ft_calloc(((words = count_words(s, c)) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	arr[words] = NULL;
	while (*s)
	{
		if (!word_start && *s != c)
			word_start = s;
		if (word_start && (*s == c || !*(s + 1)))
		{
			if (!make_word(arr, word_start, get_word_len(word_start, c)))
				return (NULL);
			word_start = NULL;
		}
		s++;
	}
	return (arr);
}
