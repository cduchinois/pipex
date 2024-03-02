/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:59:17 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/25 17:48:00 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	clean_process(t_process *process, int ac)
{
	int	i;

	if (process)
	{
		if (process->fd)
		{
			i = 0;
			while (i < ac - process->index - 2)
			{
				if (process->fd[i])
					free(process->fd[i]);
				i++;
			}
			free(process->fd);
		}
		if (process->pathname)
			ft_freetab(process->pathname);
		if (process->pid)
			free(process->pid);
		if (process->index == 3)
			unlink(".here_doc");
		free(process);
	}
}

t_process	*error_handler(t_process *process, int ac, char *error_msg)
{
	perror(error_msg);
	clean_process(process, ac);
	exit(1);
}
