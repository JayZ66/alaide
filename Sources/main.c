/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:14:33 by jeguerin          #+#    #+#             */
/*   Updated: 2024/06/05 17:48:30 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_input(t_minishell *minishell)
{
	char	*input;

	(void)minishell;
	input = readline("Tarpin_de_Minishell>");
	if (input == NULL)
	{
		free(input);
		printf("exit\n");
		minishell->last_exit_status = EXIT_FAILURE;
		free_tab(minishell->env);
		free(minishell);
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(input, ":", 1) == 0 || ft_strncmp(input, "!", 1) == 0)
	{
		input = ft_strdup("");
		return (input);
	}
	add_history(input);
	return (input);
}

// int	main(int argc, char **argv, char **env)
// {
// 	char			*input;
// 	t_minishell		exit_code;
// 	t_token			*token;
// 	t_token	*clean_token;
// 	t_token	*final_token;
// 	t_minishell		*minishell;

// 	token = NULL;
// 	(void)env;
// 	minishell = (t_minishell *)malloc(sizeof(t_minishell));
// 	manage_signals(minishell);
// 	exit_code.last_exit_status = 0;
// 	clean_token = (t_token *)malloc(sizeof(t_token));
// 	final_token = (t_token *)malloc(sizeof(t_token));
// 	if (argc != 1 || argv[1])
// 		return (perror("Wrong nb of args\n"), 1);
// 	minishell->env = realloc_env(env);
// 	if (env == NULL)
// 		return (perror("Realloc env. failed\n"), 1);
// 	while (1)
// 	{
// 		input = read_input(minishell);
// 		if (ft_strlen(input) == 0 || ft_isspace(input) == 1)
// 		{
// 			rl_on_new_line();
// 			free(input);
// 			continue ;
// 		}
// 		token = extract_cmd(&token, input);
// 		t_token	*head = token;
// 		clean_chevron(token);
// 		clean_spaces1(token);
// 		manage_node(token);
// 		clean_spaces2(token);
// 		if (verif_pipe(token) == 1)
// 		{
// 			rl_on_new_line();
// 			free(input);
// 			while (token)
// 			{
// 				free(token->content);
// 				token = token->next;
// 			}
// 			continue ;
// 		}
// 		token = head;
// 		clean_token = copy_lst(token);
// 		print_clean_lst(clean_token);
// 		test_redirection_input(clean_token);
// 		final_token = final_clean_node(clean_token);
// 		get_var_of_env(final_token);
// 		remove_quote(final_token);
// 		// check_line(&final_token, minishell, &exit_code);
// 		execute_commands_with_pipes_and_redirections(&final_token,
// 			minishell, &exit_code);
// 		free_that_lst(&token);
// 		if (clean_token)
// 			free_that_clean_lst(&clean_token);
// 		if (final_token)
// 			free_that_final_lst(&final_token);
// 		free(input);
// 	}
// 	free_tab(minishell->env);
// 	free(minishell);
// 	return (0);
// }

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_minishell		exit_code;
	t_token			*token;
	t_token			*head;
	t_token			*clean_token;
	t_token			*final_token;
	t_minishell		*minishell;

	token = NULL;
	(void)env;
	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	manage_signals(minishell);
	minishell->last_exit_status = 0;
	if (argc != 1 || argv[1])
		return (perror("Wrong nb of args\n"), 1);
	minishell->env = realloc_env(env);
	if (minishell->env == NULL)
		return (perror("Realloc env. failed\n"), 1);
	while (1)
	{
		input = read_input(minishell);
		if (ft_strlen(input) == 0 || ft_isspace(input) == 1)
		{
			rl_on_new_line();
			free(input);
			continue ;
		}
		token = extract_cmd(&token, input);
		head = token;
		// if (clean_chevron(token) == 1)
		// {
		// 	printf("bash: %s error\n", input);
		// 	rl_on_new_line();
		// 	free(input);
		// 	free_that_lst(&token);
		// 	continue ;
		// }
		clean_spaces1(token);
		manage_node(token);
		clean_spaces2(token);
		if (verif_pipe(token) == 1)
		{
			rl_on_new_line();
			free(input);
			while (token)
			{
				free(token->content);
				token = token->next;
			}
			continue ;
		}
		token = head;
		clean_token = copy_lst(token);
		free_lst_not_content(&token);
		token = NULL;
		test_redirection_input(clean_token);
		final_token = final_clean_node(clean_token);
		free_lst_not_content(&clean_token);
		get_var_of_env(final_token);
		clean_token = NULL;
		remove_quote(final_token);
		execute_commands_with_pipes_and_redirections(&final_token,
			minishell, &exit_code);
		// if (clean_token)
		// if (final_token)
		free_that_lst(&final_token);
		// final_token = NULL;
		free(input);
	}
	free_tab(minishell->env);
	free(minishell);
	return (0);
}

// antoine : dans l'etat actuel du main j'ai :

//==296259== LEAK SUMMARY:
//==296259==    definitely lost: 0 bytes in 0 blocks
//==296259==    indirectly lost: 0 bytes in 0 blocks
//==296259==      possibly lost: 0 bytes in 0 blocks
//==296259==    still reachable: 3,042 bytes in 80 blocks
//==296259==         suppressed: 208,265 bytes in 226 blocks
//==296259== 
//==296259== For lists of detected and suppressed errors, rerun with: -s
//==296259== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

// si je decommente free_that_lst j'ai :

//==296837== LEAK SUMMARY:
//==296837==    definitely lost: 0 bytes in 0 blocks
//==296837==    indirectly lost: 0 bytes in 0 blocks
//==296837==      possibly lost: 0 bytes in 0 blocks
//==296837==    still reachable: 3,042 bytes in 80 blocks
//==296837==         suppressed: 208,265 bytes in 226 blocks
//==296837== 
//==296837== For lists of detected and suppressed errors, rerun with: -s
//==296837== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

// et si je decommente les deux if (clean_token et final_token) j'ai ca :

//==296909== LEAK SUMMARY:
//==296909==    definitely lost: 0 bytes in 0 blocks
//==296909==    indirectly lost: 0 bytes in 0 blocks
//==296909==      possibly lost: 0 bytes in 0 blocks
//==296909==    still reachable: 3,042 bytes in 80 blocks
//==296909==         suppressed: 208,307 bytes in 229 blocks
//==296909== 
//==296909== For lists of detected and suppressed errors, rerun with: -s
//==296909== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

// l'erreur en question : invalid free

//==296904== Invalid free() / delete / delete[] / realloc()
//==296904==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
//==296904==    by 0x1105EF: free_that_clean_lst (init_nodes.c:94)
//==296904==    by 0x1098BE: main (main.c:172)
//==296904==  Address 0x4b62a50 is 0 bytes inside a block of size 6 free'd
//==296904==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
//==296904==    by 0x10994D: free_that_lst (utils.c:33)
//==296904==    by 0x1098A9: main (main.c:170)
//==296904==  Block was alloc'd at
//==296904==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
//==296904==    by 0x111AE5: ft_strdup (in /home/jeguerin/Documents/42_projects/Mini_rom/minishell)
//==296904==    by 0x11066D: init_node (init_nodes.c:25)
//==296904==    by 0x110FA3: tokenize_arg (tokenize.c:164)
//==296904==    by 0x1103B1: extract_cmd (extract_cmd.c:62)
//==296904==    by 0x1097BD: main (main.c:138)



// je pense donc qu'il faut se poser une petite heure autour d'un cafe et comprendre vraiment ce qui se passe
// avec les listes token, clean_token et final_token. 1. Je comprends toujours pas pourquoi y'a aucun probleme
// du cote de la premiere liste "token". Meme si les listes ne contiennent pas la meme chose techniquement si lol)
// ou ne sont pas  manipulees de la meme facon, c'est bizarre qu'il n 'y ait rien concernant cette liste.
// Comprendre comment on passe de token a clean token et de clean token a final token ca nous permettra de free
// ou il faut parce que comme tu peux le voir au dessus j'ai beau virer ou rajouter des frees les leaks restent
// inchanges, ou bien ca rajoute des invalid free. Bref see u demain, desole que ce soit pas regle :)