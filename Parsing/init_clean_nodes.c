/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clean_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:00 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/05 17:49:14 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token    *init_clean_node(char *content, Token_type type)
{
    t_token    *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (token == NULL)
    {
        perror("List has not been created\n");
        exit(EXIT_FAILURE);
    }
    token->content = ft_strdup(content);
	free(content);
    if (token->content == NULL)
    {
		free(token);
        perror("Memory allocation failde\n");
        exit(EXIT_FAILURE);
    }
	token->type = type;
    token->next = NULL;
    return (token);
}

t_token	*lst_clean_last(t_token *token)
{
	if (token == NULL)
	{
		perror("Token node is empty\n");
		exit(EXIT_FAILURE);
	}
	while (token->next)
		token = token->next;
	return (token);
}

void	add_clean_back(t_token **token, t_token *new)
{
	t_token	*last;

	// if (!(token))
	// {
	// 	perror("List is empty\n");
	// 	EXIT_FAILURE;
	// }
	if (!(*token)) // To check !
		*token = new;
	else
	{
		last = lst_clean_last(*token);
		last->next = new;
	}
}

void	print_clean_lst(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("Chaque node clean content : %s\n", tmp->content);
		printf("Chaque node clean type content : %u\n", tmp->type);
		tmp = tmp->next;
	}
}

void    free_that_clean_lst(t_token **token)
{
	t_token	*tmp;

	if (!(*token))
	{
		free(token);
		perror("Clean lst is empty, can't free\n");
		exit(EXIT_FAILURE);
	}
	while(*token)
	{
		tmp = (*token)->next;
		 if ((*token)->content)
			free((*token)->content);
		free(*token);
		*token = tmp;
	}
	*token = NULL;
}
