/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:57:37 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/25 17:55:17 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

t_process	*process_struct_init(int cmd_start_index,
			int ac, char **av, char **envp)
{
	t_process	*process;

	process = (t_process *)malloc(sizeof(t_process));
	if (!process)
		return (error_handler(process, ac,
				"Error: process struct malloc failed\n"));
	process->index = cmd_start_index;
	process->fd = create_pipes(cmd_start_index, ac);
	if (!process->fd)
		return (error_handler(process, ac, "Error: Pipe creation failed\n"));
	process->pathname = pathname_list(cmd_start_index, ac, av, envp);
	if (!process->pathname)
		return (error_handler(process, ac,
				"Error: Pathname allocation failed\n"));
	process->pid = (int *)malloc(sizeof(int) * (ac - cmd_start_index - 1));
	if (!process->pid)
		return (error_handler(process, ac, "Error: PID allocation failed\n"));
	return (process);
}

int	param_parsing(int ac, char **av)
{
	if (ac < 4)
	{
		ft_putstr_fd("Error: Too few arguments\n", 2);
		exit(1);
	}
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 5)
		{
			ft_putstr_fd("Error: Too few arguments for here_doc\n", 2);
			exit(1);
		}
		return (3);
	}
	else
		return (2);
}

void	wait_for_children(t_process *process, int ac)
{
	int	num_cmds;
	int	i;

	i = 0;
	num_cmds = ac - process->index - 1;
	while (i < num_cmds)
	{
		if (process->pid[i] > 0)
			waitpid(process->pid[i], NULL, 0);
		i++;
	}
}

int	main(int ac, char **av, char *envp[])
{
	t_process	*process;
	int			cmd_start_index;

	cmd_start_index = param_parsing(ac, av);
	process = process_struct_init(cmd_start_index, ac, av, envp);
	ft_execute(ac, av, envp, process);
	wait_for_children(process, ac);
	clean_process(process, ac);
	return (0);
}
