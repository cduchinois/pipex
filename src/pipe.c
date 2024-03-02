/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:56:05 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/25 18:13:38 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	**create_pipes(int cmd_start_index, int ac)
{
	int	**fd;
	int	i;

	i = 0;
	fd = malloc((ac - cmd_start_index - 2) * sizeof(int *));
	if (!fd)
		return (NULL);
	while (i < ac - cmd_start_index - 2)
	{
		fd[i] = malloc(2 * sizeof(int));
		if (!fd[i])
			return (NULL);
		if (pipe(fd[i]) == -1)
			return (NULL);
		i++;
	}
	return (fd);
}

int	handle_here_doc(char **av)
{
	int		fd_infile;
	char	*line;

	fd_infile = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_infile < 0)
		return (-1);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
		{
			free(line);
			break ;
		}
		write(fd_infile, line, ft_strlen(line));
		free(line);
	}
	close(fd_infile);
	return (open(".here_doc", O_RDONLY));
}

int	handle_first_command(t_process *process, char **av)
{
	int	fd_infile;

	if (process->index == 2)
	{
		fd_infile = open(av[1], O_RDONLY);
	}
	else
	{
		fd_infile = handle_here_doc(av);
	}
	return (fd_infile);
}

void	ft_fd_in(int i, int ac, t_process *process, char **av)
{
	int	fd_infile;

	if (i == 0)
	{
		fd_infile = handle_first_command(process, av);
		if (fd_infile < 0)
			error_handler(process, ac, "Error opening input file");
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
	else
	{
		dup2(process->fd[i - 1][0], STDIN_FILENO);
		close(process->fd[i - 1][0]);
		close(process->fd[i - 1][1]);
	}
}

void	ft_fd_out(int i, int ac, t_process *process, char *outfile)
{
	int	fd_outfile;

	if (i == ac - process->index - 2)
	{
		if (process->index == 2)
			fd_outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
		{
			fd_outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (fd_outfile < 0)
			error_handler(process, ac, "Error opening output file");
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
	else
	{
		dup2(process->fd[i][1], STDOUT_FILENO);
		close(process->fd[i][0]);
		close(process->fd[i][1]);
	}
}
