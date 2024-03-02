/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:34:10 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/25 17:47:45 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "../src/libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_process
{
	int		index;
	int		**fd;
	char	**pathname;
	int		*pid;
}	t_process;

int			**create_pipes(int cmd_start_index, int ac);
char		**pathname_list(int cmd_start_index, int ac,
				char **av, char **envp);
void		ft_fd_in(int i, int ac, t_process *process, char **av);
void		ft_fd_out(int i, int ac, t_process *process, char *outfile);
void		ft_execute(int ac, char **av, char **envp, t_process *process);
void		clean_process(t_process *process, int ac);
t_process	*error_handler(t_process *process, int ac, char *error_msg);

#endif