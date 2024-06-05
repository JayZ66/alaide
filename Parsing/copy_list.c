/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:09:29 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/05 17:54:38 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *copy_lst(t_token *token)
{
    // t_token *head = token;
    t_token *clean_list = NULL;
    char *content = NULL;
    t_token *block_start = token; // Pointeur de départ pour le bloc actuel
    t_token *new;

    while (token != NULL)
    {
        block_start = token;
        while (token != NULL && token->type != PIPE)
        {
            if (token->type == INPUT || token->type == HERE_DOC)
            {
				if (!token || string_is_space(token->content) == 1)
				{
					printf("syntax error \n");
					return (NULL);
				}
                content = token->content;
                new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                // free(content);
            }
            token = token->next;
        }

        // Ajouter les arguments pour ce bloc
        token = block_start;
        while (token != NULL && token->type != PIPE)
        {
            if (token->type == CMD)
            {
				if (ft_strncmp(token->content, "&&", 2) == 0)
				{
					printf("syntax error &&\n");
					return (NULL);
				}
                content = token->content;
                new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                // free(content);
            }
            token = token->next;
        }

        // Ajouter les sorties pour ce bloc
        token = block_start;
        while (token != NULL && token->type != PIPE)
        {
            if (token->type == OUTPUT || token->type == APPEND)
            {
				if (!token || string_is_space(token->content) == 1)
				{
					printf ("syntax error\n");
					return (NULL);
				}
                content = token->content;
                new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                // free(content);
            }
            token = token->next;
        }

        // Passer au prochain bloc s'il y en a un
        if (token!= NULL)
        {
			if (token->type == PIPE)
			{
				content = ft_strdup("|");
                new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                // free(content);
			}
            token = token->next; // Avancer pour sauter le pipe
        }
    }
    // free_that_lst(&token);
    return (clean_list);
}


t_token *final_clean_node(t_token *token)
{
    t_token *final_token = NULL;
    char *content = NULL;

    while (token)
    {
        while (token && (token->type == INPUT || token->type == HERE_DOC))
        {
			if (!token->next || (token->next->type != INPUT && token->next->type != HERE_DOC))
			{
            	content = token->content;
            	t_token *new = init_final_node(content, token->type);
            	add_final_back(&final_token, new);
            	// free(content);
			}
            token = token->next;
        }

        while (token && token->type == CMD)
        {
            content = token->content;
            t_token *new = init_final_node(content, token->type);
            add_final_back(&final_token, new);
            // free(content);
            token = token->next;
        }

        while (token && (token->type == OUTPUT || token->type == APPEND))
        {
            if (!token->next || token->next->type == PIPE)
            {
                content = token->content;
                t_token *new = init_final_node(content, token->type);
                add_final_back(&final_token, new);
                // free(content);
            }
            token = token->next;
        }

        if (token && token->type == PIPE)
        {
            content = "|";
            t_token *new = init_final_node(content, token->type);
            add_final_back(&final_token, new);
            // free(content);
            token = token->next;
        }
    }
    return (final_token);
}



t_token	*init_final_node(char *content, Token_type type)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		perror("List has not been created\n");
		exit(EXIT_FAILURE);
	}
	token->content = content;
	if (token->content == NULL)
	{
		perror ("Memory allocation failed\n");
		exit (EXIT_FAILURE);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*lst_final_last(t_token	*token)
{
	if (token == NULL)
	{
		perror ("Token node is empty\n");
		exit(EXIT_FAILURE);
	}
	while (token->next)
		token = token->next;
	return (token);
}

void	add_final_back(t_token **token, t_token *new)
{
	t_token	*last;
	if (!(*token))
		*token = new;
	else
	{
		last = lst_final_last(*token);
		last->next = new;
	}
}

void	print_final_lst(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("Chaque node finale content : %s\n", tmp->content);
		printf("Chaque node finale type content : %u\n", tmp->type);
		tmp = tmp->next;
	}
}
