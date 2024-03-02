/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:39:25 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/25 18:10:02 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	**find_path_from_envp(char **envp, const char *var_name)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0)
		{
			path = ft_split((envp[i] + ft_strlen(var_name) + 1), ':');
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*get_first_word(char *str)
{
	int		i;
	int		len;
	char	*first_word;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	len = i;
	first_word = malloc(len + 1);
	if (!first_word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		first_word[i] = str[i];
		i++;
	}
	first_word[i] = '\0';
	return (first_word);
}

char	*create_full_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

char	*find_pathname(char **path, char *command_str)
{
	char	*cmd;
	char	*pathname;

	cmd = get_first_word(command_str);
	if (!cmd)
		return (NULL);
	if (!path)
	{
		if (access(cmd, F_OK & X_OK) == 0)
			return (cmd);
	}
	while (*path)
	{
		pathname = create_full_path(*path, cmd);
		if (pathname && access(pathname, F_OK & X_OK) == 0)
		{
			free(cmd);
			return (pathname);
		}
		free(pathname);
		path++;
	}
	free(cmd);
	return (NULL);
}

char	**pathname_list(int cmd_start_index, int ac, char **av, char **envp)
{
	char	**pathname;
	char	**path;
	int		i;

	path = find_path_from_envp(envp, "PATH");
	pathname = malloc (sizeof(char *) * (ac - cmd_start_index));
	if (!pathname)
		return (NULL);
	i = 0;
	while (i < ac - cmd_start_index - 1)
	{
		pathname[i] = find_pathname(path, av[cmd_start_index + i]);
		i++;
	}
	ft_freetab(path);
	pathname[i] = NULL;
	return (pathname);
}
