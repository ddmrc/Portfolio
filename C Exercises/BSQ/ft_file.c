/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemarco <ddemarco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:23:07 by ddemarco          #+#    #+#             */
/*   Updated: 2022/03/03 18:04:54 by ddemarco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h> 

int	ft_power(int nb, int power);

int	ft_get_len(int *is_readed, char str_c[1000], char *c, int f_desc)
{
	int	i;

	i = 0;
	*is_readed = read(f_desc, c, 1);
	while (*is_readed > 0 && *c != '\n')
	{
		str_c[i++] = *c;
		*is_readed = read(f_desc, c, 1);
	}
	return (i);
}

int	ft_read_first_line(int *lines, char signs[3], int f_desc)
{
	int		i[2];
	char	c;
	int		i_sign;
	int		is_readed;
	char	str_c[1000];

	i[0] = ft_get_len(&is_readed, str_c, &c, f_desc);
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

char	*ft_read_file(char *path, int *lines, int *columns, char signs[3])
{
	int		file_descriptor;
	int		is_readed;
	char	c;
	char	*str;
	int		index;

	if (path[0] == '0')
		file_descriptor = STDIN_FILENO;
	else
		file_descriptor = open(path, O_RDONLY);
	is_readed = ft_read_first_line(lines, signs, file_descriptor);
	str = malloc(sizeof(char) * 100000000);
	index = 0;
	while (is_readed > 0)
	{
		if (c == '\n' && *columns <= 0)
			*columns = index - 1;
		is_readed = read(file_descriptor, &c, 1);
		str[index] = c;
		index++;
	}
	str[index] = '\0';
	return (str);
}
