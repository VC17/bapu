/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchandra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 20:08:33 by vchandra          #+#    #+#             */
/*   Updated: 2018/03/14 20:08:48 by vchandra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list			*get_correct_file(t_list **file, int fd)
{
	t_list				*tmp;

	tmp = *file;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(file, tmp);
	tmp = *file;
	return (tmp);
}

int						get_next_line(const int fd, char **line)
{
	char				buf[BUFF_SIZE + 1];
	static t_list		*file;
	int					i;
	int					ret;
	t_list				*curr;

	if ((fd < 0 || line == NULL || read(fd, buf, 0) < 0))
		return (-1);
	curr = get_correct_file(&file, fd);
	MALLCHECK((*line = ft_strnew(1)));
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		MALLCHECK((curr->content = ft_strjoin(curr->content, buf)));
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < BUFF_SIZE && !ft_strlen(curr->content))
		return (0);
	i = ft_copyuntil(line, curr->content, '\n');
	(i < (int)ft_strlen(curr->content))
		? curr->content += (i + 1)
		: ft_strclr(curr->content);
	return (1);
}

