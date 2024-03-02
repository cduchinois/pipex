/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:58:05 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/25 17:48:06 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_execve(int i, t_process *process, char **av, char *envp[])
{
	char	**exec_arg;

	if (!process->pathname[i])
	{
		exec_arg = (char *[]){"/bin/sh", "-c", av[process->index + i], NULL};
		execve("/bin/sh", exec_arg, envp);
	}
	else
	{
		exec_arg = ft_split(av[process->index + i], ' ');
		if (!exec_arg)
		{
			perror("Split failed");
			exit(1);
		}
		execve(process->pathname[i], exec_arg, envp);
		ft_freetab(exec_arg);
	}
	perror("execve failed");
	exit(1);
}

void	ft_execute(int ac, char **av, char **envp, t_process *process)
{
	int (i) = 0;
	while (i < ac - process->index - 1)
	{
		process->pid[i] = fork();
		if (process->pid[i] < 0)
		{
			error_handler(process, ac, "Fork failure\n");
		}
		else if (process->pid[i] == 0)
		{
			ft_fd_in(i, ac, process, av);
			ft_fd_out(i, ac, process, av[ac - 1]);
			ft_execve(i, process, av, envp);
			exit(1);
		}
		else
		{
			if (i > 0)
				close(process->fd[i - 1][0]);
			if (i < ac - process->index - 2)
				close(process->fd[i][1]);
		}
		i++;
	}
}
