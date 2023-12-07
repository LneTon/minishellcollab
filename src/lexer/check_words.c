/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:33:54 by abertoli          #+#    #+#             */
/*   Updated: 2022/10/21 18:29:38 by abertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*create_word(char *cmd, int length, int i)
{
	char	*word;
	int		j;

	word = (char *) malloc (sizeof(char) * (length + 1));
	if (word == NULL)
		return (NULL);
	j = 0;
	while (length > 0)
	{
		word[j] = cmd[i - length];
		length--;
		j++;
	}
	word[j] = '\0';
	return (word);
}

static bool	is_word_const(char *word, t_list *env)
{
	if (is_word_env(word, env) || is_word_exit_code(word, env))
		return (true);
	return (false);
}

int	check_for_word_without_quotes(char *cmd, int i,
		t_list **tokens_list, t_list *env)
{
	int		length;
	char	*word;
	bool	is_const;

	length = calculate_word_length(cmd, i, false);
	i = i + length;
	if (length > 0)
	{
		word = create_word(cmd, length, i);
		is_const = is_word_const(word, env);
		word = check_if_env_or_exit_code(word, env);
		if (is_const)
			ft_lstadd_back(tokens_list,
				ft_lstnew(create_token(word, CONST, env)));
		else
			ft_lstadd_back(tokens_list,
				ft_lstnew(create_token(word, WORD, env)));
	}
	return (i);
}

int	check_for_word_in_single_quotes(char *cmd, int i,
			t_list **tokens_list, t_list *env)
{
	int		length;
	char	*word;

	length = 0;
	while (cmd[i] != '\'' && cmd[i] != '\0')
	{
		length++;
		i++;
	}
	if (length > 0)
	{
		word = create_word(cmd, length, i);
		ft_lstadd_back(tokens_list, ft_lstnew(create_token(word, WORD, env)));
	}
	i++;
	return (i);
}

int	check_for_word_in_double_quotes(char *cmd, int i,
			t_list **tokens_list, t_list *env)
{
	int		length;
	char	*word;
	bool	is_const;

	while (cmd[i] != '"' && cmd[i] != '\0')
	{
		length = calculate_word_length(cmd, i, true);
		i = i + length;
		if (length > 0)
		{
			word = create_word(cmd, length, i);
			is_const = is_word_const(word, env);
			word = check_if_env_or_exit_code(word, env);
			if (is_const)
				ft_lstadd_back(tokens_list,
					ft_lstnew(create_token(word, CONST, env)));
			else
				ft_lstadd_back(tokens_list,
					ft_lstnew(create_token(word, WORD, env)));
		}
		i = check_for_spaces(cmd, i, tokens_list, env);
	}
	i++;
	return (i);
}
