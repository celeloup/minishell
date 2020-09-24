/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadier <amenadier@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 09:45:08 by celeloup          #+#    #+#             */
/*   Updated: 2020/09/24 09:08:35 by amenadier        ###   ########.fr       */
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
	int	ret;
	
	(void)argc;
	(void)argv;
	
	signal(SIGINT, control_c);
	/*signal(SIGQUIT, control_slash);
	signal(SIGTERM, signal_handler);
	if (signal(SIGCHLD, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd("SIGCHLD\n", 2);
		error_exit("signal", "failed.");
	}*/
	environment = init_env(env);
	cmd_list = NULL;
	ret = 1;
	while (ret != -1)
	{
		prompt(0);
		get_next_line(0, &input);
		if (!input)
		{
			free_env(environment);
			control_d();
		}
		else
		{
			cmd_list = parse_input(input, environment);
			//print_cmd(cmd_list, 0);
			if (cmd_list && cmd_list->argv && cmd_list->argv[0])
				ret = exec_cmds(cmd_list, &environment);
			//ft_printf("ret test = %d\n", test);
			cmd_list = free_cmd(cmd_list);
			free(input);
		}
	}
	free_env(environment);
	return (0);
}
