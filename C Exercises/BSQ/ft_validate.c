/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemarco <ddemarco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:41:25 by ddemarco          #+#    #+#             */
/*   Updated: 2022/03/03 18:10:59 by ddemarco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_get_len(int *is_readed, char str_c[1000], char *c, int f_desc);

int	ft_power(int nb, int power);

int	ft_read_first_line_verify(int *lines, char signs[3], int f_desc)
{
	int		i[2];
	char	c;
	int		i_sign;
	int		is_readed;
	char	str_c[1000];

	i[0] = ft_get_len(&is_readed, str_c, &c, f_desc);
	if (i[0] < 4)
		return (-1);
	i[1] = 0;
	i_sign = 2;
	while (--i[0] >= 0)
	{
		if ((str_c[i[0]] >= 32 && str_c[i[0]] < 127) || str_c[i[0]] > 127)
		{
			if (i_sign >= 0)
				signs[i_sign--] = str_c[i[0]];
			else
				*lines = *lines + ft_power(10, i[1]++) * (str_c[i[0]] - '0');
		}
	}
	return (is_readed);
}

int	ft_validate_signs(char signs[3])
{
	int	index;

	index = 0;
	while (index < 3)
	{
		if (signs[index] == '\0' || signs[index] == '\n' )
			return (-1);
		else if (signs[index] < 32 || signs[index] == 127)
			return (-1);
		index++;
	}
	if (signs[0] == signs[1] || signs[0] == signs[2] || signs[1] == signs[2])
		return (-1);
	return (1);
}

int	ft_validate_length_line(char c, int index, int *col_index, int *columns)
{
	if (c == '\n' && *columns <= 0)
		*columns = index;
	if (c != '\n')
		*col_index = *col_index + 1;
	else if (c == '\n' && *columns > 0)
	{	
		if (*col_index != *columns)
			return (-1);
		*col_index = 0;
	}
	return (1);
}

int	ft_read_file_ver(char signs[3], int *is_readed, int fd)
{
	char	c;
	int		columns;
	int		col_index;
	int		index;

	columns = 0;
	col_index = 0;
	index = 0;
	*is_readed = read(fd, &c, 1);
	if (!c)
		return (-1);
	if (ft_validate_signs(signs) < 0)
		return (-1);
	while (*is_readed > 0)
	{
		if (ft_validate_length_line(c, index, &col_index, &columns) < 0)
			return (-1);
		if (c != signs[0] && c != signs[1] && c != signs[2] && c != '\n')
			return (-1);
		*is_readed = read(fd, &c, 1);
		index++;
	}
	return (1);
}

int	ft_validate(char *path)
{
	int		result;
	int		*line_col;
	int		is_readed;
	int		file_descriptor;
	char	signs[3];

	line_col = malloc(sizeof(line_col) * 2);
	if (path[0] == '0')
		file_descriptor = STDIN_FILENO;
	else
		file_descriptor = open(path, O_RDONLY);
	is_readed = ft_read_first_line_verify(&line_col[0], signs, file_descriptor);
	if (is_readed == -1)
		return (-1);
	result = ft_read_file_ver(signs, &is_readed, file_descriptor);
	free(line_col);
	return (result);
}
