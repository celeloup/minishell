/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadier <amenadier@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 09:45:08 by celeloup          #+#    #+#             */
/*   Updated: 2020/09/23 15:25:53 by amenadier        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

    void
print_args(int argc, char **argv)
{  
    int i;

    ft_printf("\nARGV = ");
    i = 0;
    while (i < argc)
    {
        if (argv[i])
            ft_printf("%s,", argv[i]);
        else
            ft_printf("argc > argv count...");
        i++;
    }
}
    void
print_cmd_rdir(t_rdir *rdir)
{
    char *type;

    if (!rdir)
    {
        ft_printf("\ntrying to print a null rdir vector");
        return ;
    }
    type = NULL;
    if (rdir->type == RDIR_IN)
        type = ft_strdup("<");
    else if (rdir->type == RDIR_OUT)
        type = ft_strdup(">");
    else
        type = ft_strdup(">>");
    ft_printf("%s '%s' ", type, rdir->value);
    free(type);
    type = NULL;
    if (rdir->next)
        print_cmd_rdir(rdir->next);
}
    
    void
print_cmd(t_cmd *cmd, int i)
{
    if (!cmd)
    {
        ft_printf("\nNO CMD LIST TO PRINT");
        return ;
    }
    ft_printf("\n----CMD%d----", i);
    if (cmd->argc)
        ft_printf("\nARGC = %d", cmd->argc);
    if (cmd->argc && cmd->argv)
        print_args(cmd->argc, cmd->argv);
    else
        ft_printf("\nARGV = no arg found");
    if (cmd->rdir)
    {
        ft_printf("\nRDIR = ");
        print_cmd_rdir(cmd->rdir);
    }
    else
        ft_printf("\nRDIR = no rdir found");
    ft_printf("\nPIPE = %d", cmd->pipe);
    if (cmd->next)
    {
        ft_printf("\nNext command...");
        print_cmd(cmd->next, i + 1);
    }
    else
        ft_printf("\nlast command printed");
}
