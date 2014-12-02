/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getinfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 11:58:03 by hhismans          #+#    #+#             */
/*   Updated: 2014/12/01 21:35:28 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "fdf.h"
#include <math.h>
#include <stdlib.h>

static int		*filltab(char **tab_char)
{
	int size;
	int i;
	int *tab_int;

	size = 0;
	while (tab_char[size])
		size++;
	tab_int = (int *)ft_memalloc(sizeof(int) * (size + 1));
	tab_int[0] = size;
	i = 1;
	while (i < size + 1)
	{
		tab_int[i] = ft_atoi(tab_char[i - 1]);
		i++;
	}
	return (tab_int);
}

static int		fill_list(char *file, t_list **lst_line)
{
	int		nbr_line;
	t_list	*tmp;
	int		fd;
	int		ret;
	char	*line;

	nbr_line = 0;
	fd = open(file, O_RDONLY);
	if ((ret = get_next_line(fd, &line)))
	{
		*lst_line = ft_lstnew(line, sizeof(char) * (ft_strlen(line) + 1));
		nbr_line++;
		free(line);
	}
	tmp = *lst_line;
	while ((ret = get_next_line(fd, &line)))
	{
		tmp->next = ft_lstnew(line, sizeof(char) * (ft_strlen(line) + 1));
		tmp = tmp->next;
		nbr_line++;
	}
	close(fd);
	return (nbr_line);
}

int				**getinfo(t_env *e, char *file)
{
	char	**tab_char;
	int		nbr_line;
	int		i;
	int		**tab_int;
	t_list	*lst_line;

	i = 0;
	nbr_line = fill_list(file, &lst_line);
	tab_int = (int **)ft_taballoc(sizeof(int) * (nbr_line));
	e->nbr_line = nbr_line;
	while (lst_line)
	{
		tab_char = ft_strsplit((char *)lst_line->content, ' ');
		tab_int[i] = filltab(tab_char);
		i++;
		lst_line = lst_line->next;
	}
	return (tab_int);
}
