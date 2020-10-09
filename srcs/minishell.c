/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 09:45:08 by celeloup          #+#    #+#             */
/*   Updated: 2020/10/09 17:04:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

//valgrind --leak-check=full --show-leak-kinds=all ./minishell > valgrind_log 2>&1


/*
** Affiche le prompt en couleurs
** Si y'a eu erreur avant, affiche flèche en rouge, sinon vert
*/

void	prompt(int error)
{
	/*
	if (error == 1)
		ft_printf("%s➜  %sminishell %s> %s", RED, BLUE, YELLOW, END);
	else
		ft_printf("%s➜  %sminishell %s> %s", GREEN, BLUE, YELLOW, END);
	*/
	(void)error;
	ft_printf("➜ minishell > ");
}

int		main(int argc, char *argv[], char *env[])
{
	char	*input;
	t_cmd	*cmd_list;
	char	**environment;
	int		status;
	
	(void)argc;
	(void)argv;
	
	signal(SIGINT, control_c);
	input = NULL;
	/*signal(SIGQUIT, control_slash);
	signal(SIGTERM, signal_handler);
	if (signal(SIGCHLD, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd("SIGCHLD\n", 2);
		error_exit("signal", "failed.");
	}*/
	environment = init_env(env);
	cmd_list = NULL;
	status = 0;
//	input = ft_strdup("echo $PATH");
	while (status != -1 && status != 255)//input à enlever
	{
		prompt(0);
		get_next_line(0, &input);
		if (!input && !(environment = free_and_null_tab(&environment)))
			control_d();
		else
		{
			edit_exit_status(&environment, status);
			cmd_list = give_cmd_birth(input);
			//print_cmd(cmd_list, 0);
			if (cmd_list && cmd_list->argv && cmd_list->argv[0])
				status = exec_cmds(cmd_list, &environment);
			else if (!cmd_list)//cas de unexpected token...
				status = 2;
			//ft_printf("ret test = %d\n", test);
		}
		cmd_list = free_and_null_cmd(&cmd_list);
		input = free_and_null_str(&input);
	}
	input = free_and_null_str(&input);
	input = get_var_value("$?", environment);
	status = ft_atoi(input);
	input = free_and_null_str(&input);
	environment = free_and_null_tab(&environment);
	return (status);
}
