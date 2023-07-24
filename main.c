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

#include "minishell.h"

void clear()
{
    // Clearing the shell using escape sequences
    printf("\033[H\033[J");
}
  
void init_shell()
{
    printf("\n\n\n\n******************"
        "************************");
    printf("\n\n\n\t****MY SHELL****");
    printf("\n\n\n\n*******************"
        "***********************");
    printf("\n");
    sleep(3);
    clear();
}

void    print_token(void *content)
{
    t_token *token;

    token = (t_token*) content;
    printf("Content: %s\n", token->content);
    printf("Type: %d\n", token->type);
    printf("\n");
}

int main()
{
    char* cmd;
    t_list  *tokens_list;

    init_shell();
    while (42)
    {
        cmd = readline("*** ");
        tokens_list = lexer(cmd);
        // Lexer Test
        ft_lstiter(tokens_list, print_token);
    }
}
