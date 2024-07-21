/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:02:57 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/07/21 14:47:55 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "./libft/libft.h"

typedef struct s_elem {
	int		*pipefd;
	int		infile;
	int		outfile;
	int		num_cmds;
}	t_elem;

void	ft_error(char *s);
char	*find_path(char *command, char **env);
void	free_paths(char **paths);

#endif